
#include <cell/assert.h>
#include <cell/io.h>
#include <cell/string.h>
#include <cell/array.h>
#include <cell/slice.h>

TEST(slice_append_test) {
    cell_error err;

    if((err = cell_io_printf("slice append test\n")) != CELL_NULL) {
        cell_io_printf(err->string(err));
        return;
    }

    cell_array_make(arr, 10, int);

    cell_assert(arr.len == 10);

    cell_array_sliceof(arr, 1, 2, s);

    cell_assert(s.len == 1);
    cell_assert(s.cap == 9);

    cell_slice_append(s, 12, s);

    cell_assert(s.len == 2);

    cell_slice_for3(i, e, s) {
        if((err = cell_io_printf(cell_string_c("s[%u] = %d"), i, e)) != CELL_NULL) {
            cell_io_printf(err->string(err));
            return;
        }

        if(i == 0)
            cell_assert(e == 0);
        else if(i == 1)
            cell_assert(e == 12);
        else
            cell_assert(0);

        cell_io_printf(cell_string_c(" - ok\n"));
    }

    cell_io_printf(cell_string_c("slice append test - ok\n"));
}
