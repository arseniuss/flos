
#include <cell/io.h>
#include <cell/lang/source.h>

TEST(source_test1) {
    cell_error err;
    cell_lang_source src;

    if((err = cell_lang_source_new(cell_string_c("tests/unicode.cell"), &src)) != CELL_NULL) {
        cell_string str = err->string(err);

        cell_io_printf("error %S\n");
        return;
    }
}
