
#include <cell/io.h>
#include <cell/lang/source.h>

#include "../internal.h"

TEST(source_test1) {
    cell_error err;
    cell_lang_source src;

    cell_io_printf("source test 1\n");

    if((err = cell_lang_source_new(cell_string_c("tests/unicode.cell"), &src)) != CELL_NULL) {
        cell_io_printf("tests/unicode.cell error %S\n", err->string(err));
        return;
    }

    cell_char ch;
    cell_slice_make_generic(buf, 4096);
    cell_lang_position pos;

    while((err = __source_file_read(src, &ch, &buf, &pos)) == CELL_NULL) {
        if(ch == -1)
            break;
        cell_io_printf("file:%d:%d: char %u: %*s\n", pos.line, pos.offset, ch, buf.len, buf.buf);
        buf.len = 0;
    }

    if(err != CELL_NULL) {
        cell_io_printf("read error: %S\n", err->string(err));
        return;
    }

    cell_io_printf("source test 1 done\n");
}

const char *src_code = "var test int = 0";

TEST(source_test2) {
    cell_error err;
    cell_lang_source src;
    cell_string str = cell_string_c(src_code);

    cell_io_printf("source test 2\n");

    if((err = cell_lang_source_string(str, &src)) != CELL_NULL) {
        cell_io_printf("string source error %S\n", err->string(err));
        return;
    }

    cell_char ch;
    cell_slice_make_generic(buf, 4096);
    cell_lang_position pos;

    while((err = __source_str_read(src, &ch, &buf, &pos)) == CELL_NULL) {
        if(ch == -1)
            break;
        cell_io_printf("file:%d:%d: char %u: %*s\n", pos.line, pos.offset, ch, buf.len, buf.buf);
        buf.len = 0;
    }

    if(err != CELL_NULL) {
        cell_io_printf("read error: %S\n", err->string(err));
        return;
    }


    cell_io_printf("source test 2 done\n");
}
