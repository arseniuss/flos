
#include <cell/assert.h>
#include <cell/io.h>
#include <cell/string.h>
#include <cell/array.h>
#include <cell/slice.h>

TEST(slice_append_test1) {
    cell_error err;

    if((err = cell_io_printf("slice_append_test1\n")) != CELL_NULL) {
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
        if((err = cell_io_printf(cell_string_c("s[%u] = %d "), i, e)) != CELL_NULL) {
            cell_io_printf(err->string(err));
            return;
        }

        if(i == 0)
            cell_assert(e == 0);
        else if(i == 1)
            cell_assert(e == 12);
        else
            cell_assert(0);

        cell_io_printf(cell_string_c(" ok\n"));
    }

    cell_io_printf(cell_string_c("slice_append_test1 - ok\n"));
}

TEST(slice_append_test2) {
    cell_error err;

    if((err = cell_io_printf("slice_append_test2\n")) != CELL_NULL) {
        cell_io_printf(err->string(err));
        return;
    }

    cell_array_make(arr, 10, void *);

    cell_array_sliceof(arr, 3, 4, s);

    cell_assert(s.len == 1);
    cell_assert(s.cap == 7);

    cell_slice_append(s, (void *)10, s);

    cell_assert(s.len == 2);

    cell_slice_for3(i, e, s) {
        if((err = cell_io_printf(cell_string_c("s[%u] = %d "), i, e)) != CELL_NULL) {
            cell_io_printf(err->string(err));
            return;
        }

        if(i == 1)
            cell_assert(e == (void *)10);

        cell_io_printf(cell_string_c(" ok\n"));
    }

    cell_io_printf(cell_string_c("slice_append_test1 - ok\n"));
}
