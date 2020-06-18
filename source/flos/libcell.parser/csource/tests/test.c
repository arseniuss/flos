#include <cell/io.h>

#include "internal.h"

const char *source = "module test\n" "" "";

static void __print_error(cell_lang_parser_error * err) {
    cell_io_printf("%S:%i:%i: %S\n", err->src, err->pos.start, err->pos.end, err->msg);
}

TEST(string_parsing) {
    cell_error err;

    cell_io_printf_s(cell_string_c("STRING PARSING TEST\n"));

    cell_lang_parser prs;
    cell_lang_scanner scn;
    cell_lang_source src;

    if((err = cell_lang_source_string(cell_string_c(source), &src)) != CELL_NULL) {
        cell_io_printf_s(err->string(err));
        return;
    }

    if((err = cell_lang_scanner_new(&scn, src)) != CELL_NULL) {
        cell_io_printf_s(err->string(err));
        return;
    }

    if((err = cell_lang_parser_new(&prs, scn)) != CELL_NULL) {
        cell_io_printf_s(err->string(err));
        return;
    }

    cell_lang_ast_node *tree;

    if((err = cell_lang_parser_parse(prs, &tree)) != CELL_NULL) {
        cell_io_printf_s(err->string(err));
        return;
    }

    if(cell_lang_parser_has_error(prs)) {
        cell_io_printf("ERROR\n");

        cell_lang_parser_for_error(prs, __print_error);
    }

    cell_lang_ast_visit(tree, &visit);

    cell_io_printf_s(cell_string_c("ALL DONE\n"));
}
