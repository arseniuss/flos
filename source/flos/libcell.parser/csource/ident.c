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

cell_lang_ast_ident **cell_lang_parser_parse_ident_section(cell_lang_parser prs, cell_lang_ast_ident ** ident) {
    if(prs->tok != CELL_LANG_TIDENT) {
        cell_lang_parser_expect(prs, CELL_LANG_TIDENT);

        return CELL_NULL;
    } else {
        cell_error err;

        if((err = cell_mem_alloc(sizeof(cell_lang_ast_ident), (void **)ident))) {
            __debug("alloc error\n");
            cell_error_label_throw(prs->err_lbl, err);
        }

        if((err = cell_string_copy_s(&(*ident)->text, &prs->str))) {
            __debug("alloc error\n");
            cell_error_label_throw(prs->err_lbl, err);
        }

        cell_lang_parser_next(prs);

        return &((*ident)->next);
    }
}

void cell_lang_parser_parse_ident(cell_lang_parser prs, cell_string * str) {
    if(cell_lang_parser_expect(prs, CELL_LANG_TIDENT)) {
        cell_error err;

        if((err = cell_string_copy_s(str, &prs->str))) {
            __debug("alloc error\n");
            cell_error_label_throw(prs->err_lbl, err);
        }

        cell_lang_parser_next(prs);
    }
}

void cell_lang_parser_parse_ident_path(cell_lang_parser prs, cell_lang_ast_ident ** base) {
    cell_lang_ast_ident **ident = cell_lang_parser_parse_ident_section(prs, base);

    while(prs->tok == CELL_LANG_TDOT) {
        cell_lang_parser_next(prs);

        if(prs->tok != CELL_LANG_TIDENT)
            break;

        cell_lang_parser_parse_ident_section(prs, ident);
    }
}
