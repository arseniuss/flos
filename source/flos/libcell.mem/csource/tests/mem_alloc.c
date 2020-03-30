#include <cell/error.h>
#include <cell/io.h>
#include <cell/mem.h>
#include <cell/os/proc.h>

TEST(mem_alloc_test) {
    for(cell_int32 i = 0; i < 100; i++) {
        cell_size sz = (i % 45) * 100 + 3;
        int *ptr;
        cell_error err = cell_mem_alloc(sz, (void **)&ptr);

        if(ptr == CELL_NULL) {
            cell_io_printf_s(cell_string_c("mem_alloc(%d) returned null"));
            cell_os_exit(err->string(err));
        } else {
            cell_io_printf_s(cell_string_c("mem_alloc(%d) returned %#x\n"), sz, ptr);
        }

        *ptr = 123;
    }

    cell_io_printf_s(cell_string_c("DONE\n"));
}
