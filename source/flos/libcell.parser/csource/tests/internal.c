#include <cell/io.h>

#include "internal.h"

static void test_visit_module(const cell_lang_ast_module * module) {
    cell_io_printf("MODULE");

    cell_lang_ast_ident *ident = module->name;
    while(ident != CELL_NULL) {
        cell_io_printf(" %S", ident->text);
        ident = ident->next;
    }
    cell_io_printf("\n");
}

const cell_lang_ast_visit_if visit = {
    .visit_module = &test_visit_module
};

static void __print_error(cell_lang_parser_error * err) {
    cell_io_printf("%s:%i:%i: %S\n", "<undefined>", err->pos.start, err->pos.end, err->msg);
}

void parse_file(const char *filename) {
    cell_error err;

    cell_io_printf("FILE PARSING TEST %s\n", filename);

    cell_lang_parser prs;
    cell_lang_scanner scn;
    cell_lang_source src;

    if((err = cell_lang_source_new(cell_string_c(filename), &src)) != CELL_NULL) {
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
        return;
    }

    cell_lang_ast_visit(tree, &visit);

    cell_io_printf("ALL DONE %s\n", filename);
}
