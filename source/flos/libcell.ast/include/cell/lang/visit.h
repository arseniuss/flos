/**
 *  Cell language AST library
 *  Copyright (C) 2019  Armands Arseniuss Skolmeisters
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

#ifndef __CELL__LANG_VISIT_H__
#    define __CELL__LANG_VISIT_H__

#    include <cell/lang/ast.h>

typedef struct cell_lang_ast_visit_if_s {
    cell_bool(*visit_module) (const cell_lang_ast_module * module, void *data);
    cell_bool(*visit_import) (const cell_lang_ast_import * import, void *data);
    cell_bool(*visit_var) (const cell_lang_ast_var * variable, void *data);

    cell_bool(*visit_unrecognised) (const cell_lang_ast_node * node, void *data);
    cell_bool(*post_visit) (const cell_lang_ast_node * node, void *data);
} cell_lang_ast_visit_if;

void cell_lang_ast_visit(const cell_lang_ast_node * node, const cell_lang_ast_visit_if * visit, void *data);

#endif /* __CELL__LANG_VISIT_H__ */
