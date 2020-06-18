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

void cell_lang_parser_parse_module(cell_lang_parser prs, cell_lang_ast_node ** node) {
    cell_error err;
    cell_lang_parser_expect(prs, CELL_LANG_TMODULE);

    cell_lang_ast_module *module = CELL_NULL;
    if((err = cell_mem_alloc(sizeof(cell_lang_ast_module), (void **)&module)) != CELL_NULL) {
        cell_error_label_throw(prs->err_lbl, err);
        return;
    }

    cell_lang_ast_ident **ident = cell_lang_parser_parse_ident(prs, &module->name);

    while(prs->tok == CELL_LANG_TDOT) {
        cell_lang_parser_next(prs);

        if(prs->tok != CELL_LANG_TIDENT)
            break;

        cell_lang_parser_parse_ident(prs, ident);
    }

    cell_lang_parser_expect_semi(prs);

    *node = (cell_lang_ast_node *) module;
}
