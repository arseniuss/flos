#include <cell/builtin.h>
#include <cell/os.h>
#include <cell/os/linux/error.h>
#include <cell/os.h>

#define HAVE_MORECORE           1
#define MORECORE(sz)            __morecore(sz)
#define USE_LOCKS               1
#define LACKS_SYS_TYPES_H       1
#define ABORT                   os_exit(cell_string_c("abort"))
#define USE_DL_PREFIX           1
#define LACKS_ERRNO_H           1
#define NO_MALLOC_STATS         1
#define LACKS_TIME_H            1
#define LACKS_STDLIB_H          1
#define LACKS_STRING_H          1
#define LACKS_SYS_MMAN_H        1
#define LACKS_FCNTL_H           1
#define LACKS_UNISTD_H          1
#define HAVE_MMAP               0
#define HAVE_MREMAP             0
#define ONLY_MSPACES            0
#define MALLOC_FAILURE_ACTION   os_exit(cell_string_c("memory allocation failure"))
#define MSPACES                 0
#define LACKS_SCHED_H           1
#define LACKS_SYS_PARAM_H       1
#define MALLINFO_FIELD_TYPE     cell_size
#define size_t                  cell_size
#define ptrdiff_t               cell_ptrdiff
#define NO_MALLINFO             1

#undef R
#undef A
#undef X
#undef W

#define dlcalloc               mem_array_alloc
#define dlfree                 mem_free
#define dlmalloc               mem_alloc
#define dlmemalign             mem_align_alloc
#define dlposix_memalign       mem_align_alloc_posix
#define dlrealloc              mem_realloc
#define dlrealloc_in_place     mem_expand
#define dlvalloc               mem_alloc_page
#define dlpvalloc              __pvalloc
#define dlmallopt              __mallopt
#define dlmalloc_trim          __malloc_trim
#define dlmalloc_stats         __malloc_stats
#define dlmalloc_usable_size   __malloc_usable_size
#define dlmalloc_footprint     __malloc_footprint
#define dlmalloc_max_footprint __malloc_max_footprint
#define dlmalloc_footprint_limit __malloc_footprint_limit
#define dlmalloc_set_footprint_limit __malloc_set_footprint_limit
#define dlmalloc_inspect_all   __malloc_inspect_all
#define dlindependent_calloc   __independent_calloc
#define dlindependent_comalloc __independent_comalloc
#define dlbulk_free            mem_array_free

static void *__morecore(cell_size sz) {
    void *ptr = CELL_NULL;
    cell_error *err;

    if((err = os_sbrk(sz, &ptr)) != CELL_NULL) {
        return (void *)(~(size_t) 0);
    }

    return ptr;
}

static void *memset(void *str, int c, size_t n) {
    char *p = (char *)str;

    for(size_t i = 0; i < n; i++) {
        *p++ = c;
    }

    return str;
}

static void *memcpy(void *str1, const void *str2, size_t n) {
    char *s1 = (char *)str1;
    const char *s2 = (const char *)str2;

    while(n--)
        *s1++ = *s2++;

    return str1;
}

#include "malloc.c"
