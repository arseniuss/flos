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

cell_lang_ast_module *cell_lang_parser_parse_module(cell_lang_parser prs, cell_lang_ast_node ** node) {
    cell_error err;

    cell_lang_parser_expect(prs, CELL_LANG_TMODULE);
    cell_lang_parser_next(prs);

    cell_lang_ast_module *module = CELL_NULL;
    if((err = cell_mem_alloc(sizeof(cell_lang_ast_module), (void **)&module)) != CELL_NULL) {
        cell_error_label_throw(prs->err_lbl, err);
    }

    __builtin_memset(module, 0, sizeof(*module));
    module->base.type = CELL_LANG_AMODULE;

    cell_lang_parser_parse_ident_path(prs, &module->name);

    cell_lang_parser_expect_semi(prs);

    *node = (cell_lang_ast_node *) module;

    return module;
}

void cell_lang_parser_parse_import(cell_lang_parser prs, cell_lang_ast_module * module) {
    cell_error err;

    if(cell_lang_parser_expect(prs, CELL_LANG_TIMPORT)) {
        cell_lang_parser_next(prs);

        cell_lang_ast_import *import = CELL_NULL;
        if((err = cell_mem_alloc(sizeof(*import), (void **)&import)) != CELL_NULL) {
            cell_error_label_throw(prs->err_lbl, err);
            return;
        }

        __builtin_memset(import, 0, sizeof(*import));
        import->base.type = CELL_LANG_AIMPORT;

        cell_lang_parser_parse_ident_path(prs, &import->path);

        if(prs->tok == CELL_LANG_TEQ) {
            cell_lang_parser_next(prs);

            cell_lang_parser_parse_ident(prs, &import->alias);
        }

        if(prs->tok == CELL_LANG_TFROM) {
            cell_lang_parser_next(prs);

            cell_lang_parser_parse_str(prs, &import->location);
        }

        cell_lang_parser_expect_semi(prs);

        import->base.next = module->imports;
        module->imports = (struct cell_lang_ast_node_s *)import;
    }
}
