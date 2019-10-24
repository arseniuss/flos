#include <cell/std/io.h>
#include <cell/std/memory.h>

TEST(mem_alloc_test) {
    for(cell_int32 i = 0; i < 100000; i++) {
        cell_size sz = (i % 45) * 10 + 3;
        void *ptr = mem_alloc(sz);

        if(ptr == CELL_NULL) {
            os_exit(cell_string_c("mem_alloc() returned NULL\n"));
        } else {
            io_printf(cell_string_c("mem_alloc(%d) returned %#x\n"), sz, ptr);
        }
    }l
}
