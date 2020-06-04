#include <cell/ascii.h>
#include <cell/error.h>
#include <cell/fmt.h>
#include <cell/io.h>
#include <cell/lang/position.h>
#include <cell/lang/scanner.h>
#include <cell/lang/scanner.h>
#include <cell/lang/source.h>
#include <cell/os/proc.h>

TEST(one_line_test) {
    cell_error err;
    cell_lang_source src;
    cell_lang_scanner scn;

    if((err = cell_lang_source_new(cell_string_c("tests/one_line_test.cell"), &src)) != CELL_NULL) {
        cell_slice_make_generic(s, 256);

        cell_fmt_format(&s, cell_string_c("lang: %S"), err->string(err));

        cell_os_exit(cell_string_s(s));
    }

    if((err = cell_lang_scanner_new(&scn, src)) != CELL_NULL) {
        cell_os_exit(err->string(err));
    }

    cell_lang_token tok;
    cell_lang_range r;
    cell_string str;

    cell_lang_position_init(&r.start);
    cell_lang_position_init(&r.end);

    while((tok = cell_lang_scanner_scan(scn, &r, &str)) > CELL_LANG_TEOF) {
        cell_io_printf("\t%d:%d - %d:%d:%s ", r.start.line, r.start.offset,
                       r.end.line, r.end.offset, cell_lang_tokens[tok]);
        if(!cell_ascii_isspace(str.buffer[0])) {
            cell_io_printf(" \"%S\"", str);
        }
        cell_io_printf("\n");
    }

    if(tok != CELL_LANG_TEOF) {
        err = cell_lang_scanner_err(scn);

        cell_io_printf("failed with char: \"%S\" (%d)", str, tok);
        if(err != CELL_NULL) {
            cell_io_printf(" (%S)", err->string(err));
        }
        cell_io_printf("\n");
    }

    cell_io_printf(cell_string_c("DONE!\n"));
}
