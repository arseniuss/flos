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

#include <cell/io.h>
#include <cell/lang/ast.h>
#include <cell/lang/parser.h>
#include <cell/lang/scanner.h>
#include <cell/mem.h>
#include <cell/mem/slice.h>
#include <cell/error.h>
#include <cell/fmt.h>

#define __debug(fmt, ...) cell_io_printf(fmt, ##__VA_ARGS__)

cell_slice_type_def(cell_lang_parser_error, cell_lang_parser_error);

cell_error_def(INV, "error while reading");

struct cell_lang_parser_s {
    cell_lang_scanner scn;

    cell_lang_token tok;
    cell_lang_position pos;
    cell_string str;

    cell_error_label err_lbl;
    cell_lang_parser_error_slice_type errors;
};

// func new(scn scanner) (error, parser)

cell_error cell_lang_parser_new(cell_lang_parser * prs, cell_lang_scanner scn) {
    cell_error err;
    cell_lang_parser p;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_parser_s), (void **)&p)) != CELL_NULL)
        return err;

    p->scn = scn;
    p->tok = CELL_LANG_TINVALID;
    cell_lang_position_init(&p->pos);
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

void cell_lang_parser_for_error(cell_lang_parser prs, void (*fn) (cell_lang_parser_error * err)) {
    cell_size i = 0;

    for(cell_lang_parser_error * e = &prs->errors.buf[0]; i < prs->errors.len; e = &prs->errors.buf[++i]) {
        fn(e);
    }
}

void cell_lang_parser_next(cell_lang_parser prs) {
    prs->tok = cell_lang_scanner_scan(prs->scn, &prs->pos, &prs->str);

    if(prs->tok == CELL_LANG_TINVALID)
        cell_error_label_throw(prs->err_lbl, __INV_error);

    __debug("cell_lang_parser_next %d\n", prs->tok);
}

void cell_lang_parser_expected(cell_lang_parser prs, cell_lang_position pos, cell_lang_token tok) {
    cell_error err;
    cell_lang_parser_error *prs_err;

    if((err = cell_mem_alloc(sizeof(cell_lang_parser_error), (void **)&prs_err)) != CELL_NULL) {
        cell_error_label_throw(prs->err_lbl, err);
    }

    cell_slice_type buf;

    if((err = cell_mem_alloc(256, (void **)&buf.buf)) != CELL_NULL) {
        cell_mem_free((void *)prs_err);
        cell_error_label_throw(prs->err_lbl, err);
    }
    buf.len = 0;
    buf.cap = 256;

    if((err = cell_fmt_format(&buf, cell_string_c("expected %s"), cell_lang_tokens[tok])) != CELL_NULL) {
        cell_mem_free((void *)prs_err);
        cell_mem_free((void *)buf.buf);
        cell_error_label_throw(prs->err_lbl, err);
    }

    prs_err->pos = pos;
    prs_err->msg = cell_string_s(buf);

    cell_slice_append(prs->errors, prs_err, prs->errors);
}

void cell_lang_parser_expect(cell_lang_parser prs, cell_lang_token tok) {
    cell_lang_position pos = prs->pos;

    if(prs->tok != tok) {
        cell_lang_parser_expected(prs, pos, tok);
    }

    cell_lang_parser_next(prs);
}

void cell_lang_parser_expect_semi(cell_lang_parser prs) {
    if(prs->tok != CELL_LANG_TRPAREM && prs->tok != CELL_LANG_TRCBRACK) {
        switch (prs->tok) {
            case CELL_LANG_TCOMMA:
                cell_lang_parser_expected(prs, prs->pos, CELL_LANG_TSEMICOLON);
            case CELL_LANG_TSEMICOLON:
                cell_lang_parser_next(prs);
                break;
            default:
                cell_lang_parser_expected(prs, prs->pos, CELL_LANG_TSEMICOLON);
                // TODO: goto statement end
                break;
        }
    }
}

void cell_lang_parser_parse_ident(cell_lang_parser prs, cell_lang_ast_ident ** ident) {
    __debug("cell_lang_parser_parse_ident\n");

    if(prs->tok != CELL_LANG_TIDENT) {
        cell_lang_parser_expect(prs, CELL_LANG_TIDENT);
    } else {
        cell_error err;

        if((err = cell_mem_alloc(sizeof(cell_lang_ast_ident), (void **)ident))) {
            cell_error_label_throw(prs->err_lbl, err);
        }

        cell_string_copy_s(&((*ident)->name), &prs->str);
        CELL_MEM_COPY(prs->pos, (*ident)->node.start);

        cell_lang_parser_next(prs);
    }
}

cell_error cell_lang_parser_parse(cell_lang_parser prs) {
    if(cell_error_label_init(prs->err_lbl))
        return prs->err_lbl.err;

    cell_lang_parser_expect(prs, CELL_LANG_TMODULE);

    cell_lang_ast_node *module_path = CELL_NULL;
    cell_lang_ast_ident *ident;

    cell_lang_parser_parse_ident(prs, &ident);

    module_path = &ident->node;

    while(prs->tok == CELL_LANG_TPERIOD) {
        cell_lang_parser_next(prs);

        if(prs->tok != CELL_LANG_TIDENT)
            break;

        cell_lang_parser_parse_ident(prs, &ident);

        ident->node.next = module_path;
        module_path = &ident->node;
    }

    cell_lang_parser_expect_semi(prs);

    return CELL_NULL;
}
