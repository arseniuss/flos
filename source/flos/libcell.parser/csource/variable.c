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

cell_lang_ast_node *cell_lang_parser_parse_var(cell_lang_parser prs, cell_lang_ast_node * last) {
    cell_error err;

    if(cell_lang_parser_expect(prs, CELL_LANG_TVAR)) {
        cell_lang_parser_next(prs);

        cell_lang_ast_var *variable = CELL_NULL;
        if((err = cell_mem_alloc(sizeof(*variable), (void **)&variable)) != CELL_NULL) {
            cell_error_label_throw(prs->err_lbl, err);
            return last;
        }

        __builtin_memset(variable, 0, sizeof(*variable));
        variable->base.type = CELL_LANG_AVARIABLE;

        cell_lang_parser_parse_ident(prs, &variable->name);

        cell_lang_parser_parse_type(prs, &variable->type);

        if(prs->tok == CELL_LANG_TEQ) {


            // TODO: constant expression
        }

        cell_lang_parser_expect_semi(prs);

        last->next = (cell_lang_ast_node *) variable;

        return (cell_lang_ast_node *) variable;
    }

    return last;
}
