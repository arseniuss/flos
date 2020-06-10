/**
 *  Cell language AST library
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

#include <cell/lang/ast.h>
#include <cell/lang/visit.h>

void cell_lang_ast_visit(const cell_lang_ast_node * node, const cell_lang_ast_visit_if * visit) {
    if(node == CELL_NULL || visit == CELL_NULL)
        return;

    switch (node->type) {
        case CELL_LANG_AMODULE:{
            const cell_lang_ast_module *module = (const cell_lang_ast_module *)node;

            visit->visit_module(module);
            break;
        }
        default:
            break;
    }

    if(node->next != CELL_NULL) {
        cell_lang_ast_visit(node->next, visit);
    }
}
