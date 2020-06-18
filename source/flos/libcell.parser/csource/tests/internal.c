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

static void test_visit_import(const cell_lang_ast_import * import) {
    cell_io_printf("IMPORT");

    cell_lang_ast_ident *ident = import->path;
    while(ident != CELL_NULL) {
        cell_io_printf(" %S", ident->text);
        ident = ident->next;
    }

    if(cell_string_len(import->alias) > 0)
        cell_io_printf(" ALIAS %S", import->alias);

    if(cell_string_len(import->location) > 0)
        cell_io_printf(" LOCATION %S", import->location);

    cell_io_printf("\n");
}

static void test_visit_unrecognised(const cell_lang_ast_node * node) {
    cell_io_printf("UNRECOGNISED %d", node->type);

    cell_io_printf("\n");
}

const cell_lang_ast_visit_if visit = {
    .visit_module = &test_visit_module,
    .visit_import = &test_visit_import,
    .visit_unrecognised = &test_visit_unrecognised
};

static void __print_error(cell_lang_parser_error * err) {
    cell_io_printf("%S:%i:%i: %S\n", err->src, err->pos.start, err->pos.end, err->msg);
}

void parse_file(const char *filename) {
    cell_error err;

    cell_io_printf("FILE PARSING TEST %s\n", filename);

    cell_lang_parser prs;
    cell_lang_scanner scn;
    cell_lang_source src;

    if((err = cell_lang_source_new(cell_string_c(filename), &src)) != CELL_NULL) {
        cell_io_printf("Source creation error: %S\n", err->string(err));
        return;
    }

    if((err = cell_lang_scanner_new(&scn, src)) != CELL_NULL) {
        cell_io_printf("Scanner creation error: %S\n", err->string(err));
        return;
    }

    if((err = cell_lang_parser_new(&prs, scn)) != CELL_NULL) {
        cell_io_printf("Parser creation error: %S\n", err->string(err));
        return;
    }

    cell_lang_ast_node *tree;

    if((err = cell_lang_parser_parse(prs, &tree)) != CELL_NULL) {
        cell_io_printf("Critical error while parsing: %S\n", err->string(err));
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
