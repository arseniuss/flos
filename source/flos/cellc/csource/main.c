/*
 *  Cell programming language compiler
 *  Copyright (C) 2019  Armands Arseniuss Skolmeisters
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cell/builtin.h>
#include <cell/error.h>
#include <cell/lang/ast.h>
#include <cell/lang/ir.h>
#include <cell/lang/parser.h>
#include <cell/lang/scanner.h>
#include <cell/lang/source.h>
#include <cell/lang/target.h>
#include <cell/mem.h>
#include <cell/os/proc.h>

struct list {
    char *str;
    struct list *next;
};

struct list *files = CELL_NULL;

int main(int argc, char *argv[]) {
    cell_error err;
    cell_bool param = 0;

    for(int i = 1; i < argc; i++) {
        if(param) {
            param = 0;
            continue;
        }
        if(argv[i][0] == '-') {
            param = 1;
            continue;
        }

        struct list *f;

        if((err = cell_mem_alloc(sizeof(struct list), (void **)&f))) {
            cell_os_exit(err->string(err));
        }

        f->next = files;
        f->str = argv[i];
        files = f;
    }

    if(files == CELL_NULL)
        cell_os_exit(cell_string_c("error: no input files\n"));

    for(struct list * p = files; p; p = p->next) {
        cell_lang_source src;

        cell_lang_source_new(cell_string_c(p->str), &src);

        cell_lang_target *trg = cell_lang_target_file(cell_string_c(p->str));

        cell_lang_ast *ast;

        err = cell_lang_parse(&src, &ast);
        if(err)
            cell_os_exit(err->string(err));

        err = cell_lang_asm(ast, trg);
        if(err)
            cell_os_exit(err->string(err));
    }

    return 0;
}
