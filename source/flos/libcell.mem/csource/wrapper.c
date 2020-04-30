#include <cell/mem.h>
#include <cell/error.h>

#include "dlmalloc.h"

cell_error_def(no_memory, "no memory");

cell_error mem_error = CELL_NULL;

cell_error cell_mem_alloc(cell_size sz, void **ptr) {
    mem_error = CELL_NULL;

    void *res = __malloc(sz);

    if(ptr == CELL_NULL)
        return mem_error;

    *ptr = res;

    return CELL_NULL;
}

cell_error cell_mem_realloc(cell_size sz, void **ptr) {
    mem_error = CELL_NULL;

    void *res = __realloc(*ptr, sz);

    if(res == CELL_NULL)
        return mem_error;

    *ptr = res;

    return CELL_NULL;
}

cell_error cell_mem_free(void *ptr) {
    __free(ptr);

    return CELL_NULL;
}
