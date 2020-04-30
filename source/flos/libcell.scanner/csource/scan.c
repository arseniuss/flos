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

// func (scn scanner) scan() (token, position, string)

cell_error cell_lang_scanner_skip_whitespace(cell_lang_scanner scn) {
    while(cell_utf8_isspace(scn->ch)) {

        scn->buf.len = 0;

        cell_error err;

        if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
            return err;
        }
    }

    return CELL_NULL;
}

cell_lang_token cell_lang_scanner_scan(cell_lang_scanner scn, cell_lang_position * pos, cell_string * str) {
    cell_error err;

    if(pos)
        pos->line = 0, pos->offset = 0;
    if(scn->ch == 0) {
        if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }
    }

    if((err = cell_lang_scanner_skip_whitespace(scn)) != CELL_NULL) {
        scn->err = err;
        return CELL_LANG_TINVALID;
    }

    if(scn->ch == '\'') {
        if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        if((err = cell_string_copy(str, &scn->buf, scn->buf.len - 1))) {
            scn->err = err;
            return CELL_LANG_TINVALID;
        }

        cell_slice_strip(&scn->buf, scn->buf.len - 1);

        if(scn->ch != '\'') {
            // TODO: scn->err
            return CELL_LANG_TINVALID;
        }

        return CELL_LANG_TCHAR;
    }

    if(cell_ascii_isalpha(scn->ch)) {
        do {
            if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }
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

        return CELL_LANG_TIDENT;
    }


    for(cell_size i = 0; i < sizeof(__brackets) / sizeof(__brackets[0]); i++) {
        if(scn->ch == __brackets[i].bracket) {
            if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            cell_slice_strip(&scn->buf, scn->buf.len);

            if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            return __brackets[i].token;
        }
    }

    for(cell_size i = 0; i < sizeof(__operators) / sizeof(__operators[0]); i++) {
        if(scn->ch == __operators[i].oper) {
            if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            cell_slice_strip(&scn->buf, scn->buf.len);

            if((err = scn->src->read(scn->src, &scn->ch, &scn->buf)) != CELL_NULL) {
                scn->err = err;
                return CELL_LANG_TINVALID;
            }

            return __operators[i].token;
        }
    }

    if(scn->buf.len == 0) {
        return CELL_LANG_TEOF;
    }

    if((err = cell_string_copy(str, &scn->buf, scn->buf.len))) {
        scn->err = err;
        return CELL_LANG_TINVALID;
    }

    return CELL_LANG_TINVALID;
}
