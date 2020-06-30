/**
 *  Cell language IR library
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

#include <cell/fmt.h>
#include <cell/io.h>
#include <cell/lang/ast.h>
#include <cell/lang/ir.h>
#include <cell/lang/visit.h>
#include <cell/mem/string.h>
#include <cell/mem/string.h>
#include <cell/slice.h>
#include <cell/string.h>
#include <cell/os/file.h>

typedef struct {
    cell_lang_target target;
    cell_error last_error;
} cell_asm;

static cell_bool asm_visit_module(const cell_lang_ast_module * module, void *data) {
    cell_error err;

    cell_asm *a = (cell_asm *) data;

    if((err = cell_lang_target_write(a->target, cell_string_c("; module"))) != CELL_NULL) {
        a->last_error = err;
        return 0;
    }





    return 1;
}

cell_lang_ast_visit_if asm_visit = {
    .visit_module = &asm_visit_module
};

cell_error cell_lang_asm(cell_lang_ast_node * ast, cell_lang_target target) {
    cell_asm a = {
        .last_error = CELL_NULL,
        .target = target
    };

    cell_lang_ast_visit(ast, &asm_visit, &a);

    return a.last_error;
}
