/**
 *  Cell language parser library
 *  Copyright (C) 2020  Armands Arseniuss Skolmeisters
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

#include "internal.h"

cell_error_def(INV, "error while reading");

// func new(scn scanner) (error, parser)

cell_error cell_lang_parser_new(cell_lang_parser * prs, cell_lang_scanner scn) {
    cell_error err;
    cell_lang_parser p;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_parser_s), (void **)&p)) != CELL_NULL)
        return err;

    p->scn = scn;
    p->ltok = p->tok = CELL_LANG_TINVALID;
    cell_lang_position_init(&p->pos.start);
    cell_lang_position_init(&p->pos.end);
    cell_string_init(&p->str);
    p->errors.buf = CELL_NULL;
    p->errors.cap = 0;
    p->errors.len = 0;

    *prs = p;

    return CELL_NULL;
}

cell_bool cell_lang_parser_has_error(cell_lang_parser prs) {
    return prs->errors.len > 0;
}

void cell_lang_parser_for_error(cell_lang_parser prs, void (*fn)(cell_lang_parser_error * err)) {
    cell_size i = 0;

    for(cell_lang_parser_error * e = &prs->errors.buf[0]; i < prs->errors.len; e = &prs->errors.buf[++i]) {
        fn(e);
    }
}

void cell_lang_parser_next(cell_lang_parser prs) {
    prs->ltok = prs->tok;
    prs->tok = cell_lang_scanner_scan(prs->scn, &prs->pos, &prs->str);

    if(prs->tok == CELL_LANG_TINVALID) {
        cell_error_label_throw(prs->err_lbl, __INV_error);
    }

    __debug("[%S/%s]\n", prs->str, cell_lang_tokens[prs->tok]);
}

void cell_lang_parser_new_error(cell_lang_parser prs, const cell_c_char * fmt, ...) {
    cell_error err;
    cell_lang_parser_error *prs_err;
    cell_va_list args;

    cell_va_start(args, fmt);

    if((err = cell_mem_alloc(sizeof(cell_lang_parser_error), (void **)&prs_err)) != CELL_NULL) {
        __debug("alloc error");
        cell_error_label_throw(prs->err_lbl, err);
    }

    cell_slice_type buf;

    if((err = cell_mem_alloc(256, (void **)&buf.buf)) != CELL_NULL) {
        cell_mem_free((void *)prs_err);
        __debug("alloc error\n");
        cell_error_label_throw(prs->err_lbl, err);
    }
    buf.len = 0;
    buf.cap = 256;

    if((err = cell_fmt_format_list(&buf, cell_string_c(fmt), args)) != CELL_NULL) {
        cell_mem_free((void *)prs_err);
        cell_mem_free((void *)buf.buf);
        __debug("format error\n");
        cell_error_label_throw(prs->err_lbl, err);
    }

    prs_err->pos = prs->pos;
    prs_err->msg = cell_string_s(buf);

    cell_lang_source src = cell_lang_scanner_source(prs->scn);

    if((err = cell_lang_source_name(src, &prs_err->src)) != CELL_NULL) {
        __debug("source string error\n");
        cell_error_label_throw(prs->err_lbl, err);
    }

    cell_slice_append(prs->errors, *prs_err, prs->errors);

    cell_va_end(args);
}

void cell_lang_parser_expected(cell_lang_parser prs, cell_lang_token tok) {
    cell_lang_parser_new_error(prs, "expected %s got %s", cell_lang_tokens[tok], cell_lang_tokens[prs->tok]);
}

cell_bool cell_lang_parser_expect(cell_lang_parser prs, cell_lang_token tok) {
    cell_bool res = prs->tok == tok;

    if(!res) {
        __debug("expected %s got %s\n", cell_lang_tokens[tok], cell_lang_tokens[prs->tok]);

        cell_lang_parser_expected(prs, tok);
    }

    return res;
}

void cell_lang_parser_expect_semi(cell_lang_parser prs) {
    if(prs->tok != CELL_LANG_TRPAREN && prs->tok != CELL_LANG_TRCBRACK) {
        switch (prs->tok) {
            case CELL_LANG_TCOMMA:
                cell_lang_parser_expect(prs, CELL_LANG_TSEMICOLON);
            case CELL_LANG_TSEMICOLON:
                cell_lang_parser_next(prs);
                break;
            case CELL_LANG_TEOF:
            case CELL_LANG_TNEWLINE:
                if(prs->ltok == CELL_LANG_TIDENT || prs->ltok == CELL_LANG_TSTR || prs->ltok == CELL_LANG_TRCBRACK) {
                    cell_lang_parser_next(prs);
                    break;
                }
            default:
                cell_lang_parser_expect(prs, CELL_LANG_TSEMICOLON);

                while(prs->tok != CELL_LANG_TNEWLINE && prs->tok != CELL_LANG_TEOF) {
                    __debug("SKIPPING %S\n", prs->str);
                    cell_lang_parser_next(prs);

                }
                break;
        }
    }
}

cell_error cell_lang_parser_parse(cell_lang_parser prs, cell_lang_ast_node ** node) {
    if(cell_error_label_init(prs->err_lbl)) {
        return prs->err_lbl.err;
    }

    cell_lang_parser_next(prs);

    cell_lang_ast_module *module = cell_lang_parser_parse_module(prs, node);
    cell_lang_ast_node *last_node = (cell_lang_ast_node *) module;

    while(prs->tok != CELL_LANG_TEOF) {
        switch (prs->tok) {
            case CELL_LANG_TIMPORT:
                cell_lang_parser_parse_import(prs, module);
                break;
            case CELL_LANG_TVAR:
                last_node = cell_lang_parser_parse_var(prs, last_node);
                break;
            default:
                cell_lang_parser_new_error(prs, "unrecognised token: %S (%s)", prs->str, cell_lang_tokens[prs->tok]);
                cell_lang_parser_next(prs);
                break;
        }
    }

    return CELL_NULL;
}
