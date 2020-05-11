/**
 *  Cell language scanner library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cell/array.h>
#include <cell/ascii.h>
#include <cell/assert.h>
#include <cell/error.h>
#include <cell/lang/scanner.h>
#include <cell/mem.h>
#include <cell/mem/slice.h>
#include <cell/mem/string.h>
#include <cell/utf8.h>

#include "internal.h"

struct {
    const char *keyword;
    cell_lang_token token;
} __keywords[] = {
#define __(u, l, str)    { str, CELL_LANG_T##u },
#define __TOKEN_TYPE TOKEN_KEYWORDS
#include <cell/lang/tokens.inc>
};

struct {
    const char bracket;
    cell_lang_token token;
} __brackets[] = {
#define __(u, l, str)    { str[0], CELL_LANG_T##u },
#define __TOKEN_TYPE TOKEN_BRACKETS
#include <cell/lang/tokens.inc>
};

struct {
    const char oper;
    cell_lang_token token;
} __operators[] = {
#define __(u, l, str)    { str[0], CELL_LANG_T##u },
#define __TOKEN_TYPE TOKEN_OPER
#include <cell/lang/tokens.inc>
};

cell_error_def(unclosed_char, "unclosed character literal");
cell_error_def(unclosed_str, "unclosed string literal");
cell_error_def(unexpected_eof, "unexpected end of file");

// func (scn scanner) scan() (token, position, string)

cell_error cell_lang_scanner_skip_whitespace(cell_lang_scanner scn) {
    while(cell_ascii_isblank(scn->ch)) {

        scn->buf.len = 0;

        cell_error err;

        __builtin_memcpy(&scn->last_pos, &scn->pos, sizeof(cell_lang_position));

        if((err = scn->src->read(scn->src, &scn->ch, &scn->buf, &scn->pos)) != CELL_NULL) {
            return err;
        }
    }

    return CELL_NULL;
}

cell_bool cell_lang_scanner_is_oper(cell_char ch, cell_lang_token * t) {
    cell_bool ret = 0;

    for(cell_size i = 0; i < sizeof(__operators) / sizeof(__operators[0]); i++) {
        if(ch == __operators[i].oper) {
            *t = __operators[i].token;
            return 1;
        }
    }

    return ret;
}

#define NEXT \
    __builtin_memcpy(&scn->last_pos, &scn->pos, sizeof(cell_lang_position)); \
    if ((err = scn->src->read(scn->src, &scn->ch, &scn->buf, &scn->pos)) != CELL_NULL) { \
        scn->err = err; \
        return CELL_LANG_TINVALID; \
    }

cell_lang_token cell_lang_scanner_scan(cell_lang_scanner scn, cell_lang_range * r, cell_string * str) {
    cell_error err;
    cell_lang_token token = CELL_LANG_TINVALID;

    if(scn->ch == 0) {
        NEXT;
    }

    if(scn->ch == -1) {
        str->len = 0;
        cell_slice_strip(&scn->buf, scn->buf.len);
        return CELL_LANG_TEOF;
    }

    if((err = cell_lang_scanner_skip_whitespace(scn)) != CELL_NULL) {
        scn->err = err;
        return CELL_LANG_TINVALID;
    }

    __builtin_memcpy(&r->start, &scn->last_pos, sizeof(cell_lang_position));

    if(scn->ch == '\n') {
        if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        do {
            cell_slice_strip(&scn->buf, scn->buf.len);
            NEXT;

        } while(scn->ch == '\n' && scn->ch != -1);

        cell_slice_strip(&scn->buf, scn->buf.len - 1);
        __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

        return CELL_LANG_TNEWLINE;
    }

    if(scn->ch == '"') {
        cell_slice_strip(&scn->buf, scn->buf.len);  /* Strip all */

        cell_char last;
        do {
            last = scn->ch;
            NEXT;
            if(scn->ch == -1) {
                scn->err = __unexpected_eof_error;
                return CELL_LANG_TINVALID;
            }
        } while(last == '\\' || (scn->ch != '"' && scn->ch != '\n'));

        if(scn->ch == '\n') {
            cell_slice_strip(&scn->buf, scn->buf.len - 1);

            if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            scn->err = __unclosed_str_error;
            return CELL_LANG_TINVALID;
        }

        if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len);  /* Strip all */

        NEXT;

        __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

        return CELL_LANG_TSTR;
    }

    if(scn->ch == '\'') {
        cell_slice_strip(&scn->buf, scn->buf.len);  /* Strip all */

        NEXT;

        if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len);  /* Strip all */

        NEXT;

        if(scn->ch != '\'') {
            if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            scn->err = __unclosed_char_error;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len);  /* Strip all */

        NEXT;

        __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

        return CELL_LANG_TCHAR;
    }

    if(cell_ascii_isalpha(scn->ch)) {
        do {
            NEXT;
        } while(cell_ascii_isalnum(scn->ch));

        if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len - 1);

        for(cell_size i = 0; i < sizeof(__keywords) / sizeof(__keywords[0]); i++) {
            if(cell_string_eq(str, __keywords[i].keyword))
                return __keywords[i].token;
        }

        __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

        return CELL_LANG_TIDENT;
    }

    if(cell_ascii_isdigit(scn->ch)) {
        cell_lang_token t = CELL_LANG_TINT;

        NEXT;

        switch (scn->ch) {
            case 'o':
            case 'O':
                do {
                    NEXT;
                } while((scn->ch >= '0' && scn->ch <= '7') || scn->ch == '_');
                break;
            case 'b':
            case 'B':
                do {
                    NEXT;
                } while(scn->ch == '0' || scn->ch == '1' || scn->ch == '_');
                break;
            case 'x':
            case 'X':
                do {
                    NEXT;
                } while(cell_ascii_isxdigit(scn->ch) || scn->ch == '_');
                break;
            default:
                while(cell_ascii_isdigit(scn->ch) || scn->ch == '_') {
                    NEXT;
                }
                break;
        }

        if(scn->ch == '.') {
            NEXT;

            switch (scn->ch) {
                case 'o':
                case 'O':
                    do {
                        NEXT;
                    } while((scn->ch >= '0' && scn->ch <= '7') || scn->ch == '_');
                    break;
                case 'b':
                case 'B':
                    do {
                        NEXT;
                    } while(scn->ch == '0' || scn->ch == '1' || scn->ch == '_');
                    break;
                case 'x':
                case 'X':
                    do {
                        NEXT;
                    } while(cell_ascii_isxdigit(scn->ch) || scn->ch == '_');
                    break;
                default:
                    while(cell_ascii_isdigit(scn->ch) || scn->ch == '_') {
                        NEXT;
                    }
                    break;
            }
        }

        if(scn->ch == 'e' || scn->ch == 'E') {
            NEXT;
            if(scn->ch == '+' || scn->ch == '-') {
                NEXT;
            }

            while(cell_ascii_isdigit(scn->ch) || scn->ch == '_') {
                NEXT;
            }
        }

        if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len - 1);
        __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

        return t;
    }

    for(cell_size i = 0; i < sizeof(__brackets) / sizeof(__brackets[0]); i++) {
        if(scn->ch == __brackets[i].bracket) {
            if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            cell_slice_strip(&scn->buf, scn->buf.len);

            NEXT;

            __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

            return __brackets[i].token;
        }
    }

    if(scn->ch == '/') {
        NEXT;

        if(scn->ch == '*') {
            NEXT;

            cell_slice_strip(&scn->buf, scn->buf.len);

            cell_char last;

            do {
                last = scn->ch;
                NEXT;
            } while(scn->ch != '/' && last != '*');

            if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 2))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            cell_slice_strip(&scn->buf, scn->buf.len);

            NEXT;

            __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

            return CELL_LANG_TCOMMENT;

        } else if(scn->ch == '/') {
            NEXT;

            cell_slice_strip(&scn->buf, scn->buf.len);

            while(scn->ch != '\n') {
                NEXT;
            }

            if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            cell_slice_strip(&scn->buf, scn->buf.len);

            NEXT;

            __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

            return CELL_LANG_TCOMMENT;
        }
    }


    if(cell_lang_scanner_is_oper(scn->ch, &token)) {
        do {
            NEXT;
        } while(cell_lang_scanner_is_oper(scn->ch, &token));

        if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len - 1);
        __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

        return str->len > 1 ? CELL_LANG_TOPER : token;
    }

    if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
        scn->err = err;
        return CELL_LANG_TINVALID;
    }

    __builtin_memcpy(&r->end, &scn->last_pos, sizeof(cell_lang_position));

    if(scn->buf.len == 0) {
        return CELL_LANG_TEOF;
    }

    return CELL_LANG_TINVALID;
}
