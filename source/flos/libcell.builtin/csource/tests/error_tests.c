#include <cell/io.h>
#include <cell/error.h>

TEST(error_label_test1) {
    cell_error_label errl;

    cell_io_printf("error_label_test1\n");

    if(cell_error_label_init(errl)) {
        cell_io_printf("Got error: %S\n", errl.err->string(errl.err));
    } else {
        cell_io_printf("throwing an error\n");

        cell_error_label_throw(errl, __default_error);
    }

    cell_io_printf("error_label_test1 - done\n");
}
