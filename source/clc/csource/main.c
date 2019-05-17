#include <cell/os.h>
#include <cell/builtin.h>
#include <cell/std/memory.h>
#include <cell/lang/scanner.h>
#include <cell/lang/source.h>
#include <cell/lang/ast.h>
#include <cell/lang/parser.h>
#include <cell/error.h>
#include <cell/lang/target.h>
#include <cell/lang/ir.h>

struct list {
    char *str;
    struct list *next;
};

struct list *files = CELL_NULL;

int main(int argc, char *argv[]) {
    cell_error *err;
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

        struct list *f = mem_alloc(sizeof(struct list));

        f->next = files;
        f->str = argv[i];
        files = f;
    }

    if(files == CELL_NULL)
        os_exit(cell_string_c("error: no input files\n"));

    for(struct list * p = files; p; p = p->next) {
        cell_lang_source *src = cell_lang_source_file(cell_string_c(p->str));
        cell_lang_target *trg = cell_lang_target_file(cell_string_c(p->str));

        cell_lang_ast *ast;

        err = cell_lang_parse(src, &ast);
        if(err)
            os_exit(err->string());

        err = cell_lang_asm(ast, trg);
        if(err)
            os_exit(err->string());
    }

    return 0;
}
