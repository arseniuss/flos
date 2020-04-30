#include <cell/lang/parser.h>
#include <cell/io.h>

const char *source = "module test\n" "" "";

void __print_error(cell_lang_parser_error * err) {
    cell_io_printf("%s:%i:%i: %S\n", "<undefined>", err->pos.line, err->pos.offset, err->msg);
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

    if((err = cell_lang_parser_parse(prs)) != CELL_NULL) {
        cell_io_printf_s(err->string(err));
        return;
    }

    if(cell_lang_parser_has_error(prs)) {
        cell_lang_parser_for_error(prs, __print_error);
    }


    cell_io_printf_s(cell_string_c("ALL DONE\n"));
}
