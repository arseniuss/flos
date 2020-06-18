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
    void (*visit_module)(const cell_lang_ast_module * module);
    void (*visit_import)(const cell_lang_ast_import * import);

    void (*visit_unrecognised)(const cell_lang_ast_node * node);
} cell_lang_ast_visit_if;

void cell_lang_ast_visit(const cell_lang_ast_node * node, const cell_lang_ast_visit_if * visit);

#endif /* __CELL__LANG_VISIT_H__ */
