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

#ifndef __CELL__LANG_AST_H__
#    define __CELL__LANG_AST_H__

#    include <cell/lang/position.h>

enum cell_lang_ast {
    CELL_LANG_AINVALID = -1,
#    define __(u)    CELL_LANG_A##u,
#    include <cell/lang/ast.inc>
    CELL_LANG_ALAST
};
#    undef __

typedef struct cell_lang_ast_node_s {
    enum cell_lang_ast type;
    struct cell_lang_ast_node_s *next;

    cell_lang_position start;
    cell_lang_position end;
} cell_lang_ast_node;

typedef struct cell_lang_ast_ident_s {
    cell_string text;
    struct cell_lang_ast_ident_s *next;
} cell_lang_ast_ident;

typedef struct cell_lang_ast_module_s {
    cell_lang_ast_node base;
    cell_lang_ast_ident *name;
    struct cell_lang_ast_node_s *imports;   // cell_lang_ast_import
} cell_lang_ast_module;

typedef struct cell_lang_ast_import_s {
    cell_lang_ast_node base;
    cell_lang_ast_ident *path;
    cell_string alias;
    cell_string location;
} cell_lang_ast_import;

typedef struct cell_lang_ast_type_s {
    cell_lang_ast_node base;
    cell_string name;
    struct cell_lang_ast_type_s *base_type;
    struct cell_lang_ast_type_s *sub_type;
} cell_lang_ast_type;

typedef struct cell_lang_ast_var_s {
    cell_lang_ast_node base;
    cell_string name;
    cell_lang_ast_type *type;
} cell_lang_ast_var;

void cell_lang_ast_free(cell_lang_ast_node * node);

#endif /* __CELL__LANG_AST_H__ */
