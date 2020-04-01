#include <cell/goto.h>
#include <cell/io.h>

TEST(goto_test1) {
    cell_label label;

    cell_io_printf("GOTO test\n");

    if(cell_label_init(label)) {
        cell_io_printf("label called\n");
    } else {
        cell_io_printf("making a jump\n");
        cell_label_goto(label);
    }

    cell_io_printf("done\n");
}
