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
#include <cell/mem.h>

void cell_lang_ast_visit(const cell_lang_ast_node * node, const cell_lang_ast_visit_if * visit, void *data) {
    if(node == CELL_NULL || visit == CELL_NULL)
        return;

    switch (node->type) {
        case CELL_LANG_AMODULE:{
            const cell_lang_ast_module *module = (const cell_lang_ast_module *)node;

            if(visit->visit_module)
                if(!visit->visit_module(module, data))
                    return;

            cell_lang_ast_visit(module->imports, visit, data);
            break;
        }
        case CELL_LANG_AIMPORT:{
            const cell_lang_ast_import *import = (const cell_lang_ast_import *)node;

            if(visit->visit_import)
                if(!visit->visit_import(import, data))
                    return;
            break;
        }
        case CELL_LANG_AVARIABLE:{
            const cell_lang_ast_var *variable = (const cell_lang_ast_var *)node;

            if(visit->visit_var)
                if(!visit->visit_var(variable, data))
                    return;
            break;
        }
        default:
            if(visit->visit_unrecognised)
                if(!visit->visit_unrecognised(node, data))
                    return;
            break;
    }

    if(node->next != CELL_NULL) {
        cell_lang_ast_visit(node->next, visit, data);
    }

    if(visit->post_visit)
        if(!visit->post_visit(node, data))
            return;
}

cell_bool __free_visit_module(const cell_lang_ast_module * module, void *data) {
    return 1;
}

cell_bool __free_visit_import(const cell_lang_ast_import * import, void *data) {
    return 1;
}

cell_bool __free_visit_var(const cell_lang_ast_var * variable, void *data) {
    return 1;
}

cell_bool __free_visit_unrecognised(const cell_lang_ast_node * node, void *data) {
    return 1;
}

cell_bool __free_post_visit(const cell_lang_ast_node * node, void *data) {
    cell_mem_free((void *)node);

    return 1;
}

const cell_lang_ast_visit_if __free_visit = {
    .visit_module = &__free_visit_module,
    .visit_import = &__free_visit_import,
    .visit_var = &__free_visit_var,

    .post_visit = &__free_post_visit
};

void cell_lang_ast_free(cell_lang_ast_node * node) {
    cell_lang_ast_visit(node, &__free_visit, CELL_NULL);
}
