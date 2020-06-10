#ifndef MALLOC_280_H
#    define MALLOC_280_H

#    ifdef __cplusplus
extern "C" {
#    endif

#    include <stddef.h>         /* for size_t */


#    include <cell/builtin.h>
#    include <cell/os/proc.h>
#    include <cell/os/mem.h>
#    include <cell/error.h>
#    include <cell/linux/error.h>

#    undef R
#    undef A
#    undef X
#    undef W

#    define HAVE_MORECORE           1
#    define MORECORE(sz)            __morecore(sz)
#    define USE_LOCKS               1
#    define LACKS_SYS_TYPES_H       1
#    define ABORT                   cell_os_exit_s(cell_string_c("abort"))
#    define USE_DL_PREFIX           1
#    define LACKS_ERRNO_H           1
#    define NO_MALLOC_STATS         1
#    define LACKS_TIME_H            1
#    define LACKS_STDLIB_H          1
#    define LACKS_STRING_H          1
#    define LACKS_SYS_MMAN_H        1
#    define LACKS_FCNTL_H           1
#    define LACKS_UNISTD_H          1
#    define HAVE_MMAP               0
#    define HAVE_MREMAP             0
#    define ONLY_MSPACES            0
#    define MALLOC_FAILURE_ACTION   mem_error = CELL_ERROR_NAME(no_memory)
#    define MSPACES                 0
#    define LACKS_SCHED_H           1
#    define LACKS_SYS_PARAM_H       1
#    define MALLINFO_FIELD_TYPE     cell_size
#    define size_t                  cell_size
#    define ptrdiff_t               cell_ptrdiff
#    define NO_MALLINFO             1




#    define dlcalloc               __calloc
#    define dlfree                 __free
#    define dlmalloc               __malloc
#    define dlmemalign             __memalign
#    define dlposix_memalign       __posix_memalign
#    define dlrealloc              __realloc
#    define dlrealloc_in_place     __realloc_in_plcae
#    define dlvalloc               __valloc
#    define dlpvalloc              __pvalloc
#    define dlmallopt              __mallopt
#    define dlmalloc_trim          __malloc_trim
#    define dlmalloc_stats         __malloc_stats
#    define dlmalloc_usable_size   __malloc_usable_size
#    define dlmalloc_footprint     __malloc_footprint
#    define dlmalloc_max_footprint __malloc_max_footprint
#    define dlmalloc_footprint_limit __malloc_footprint_limit
#    define dlmalloc_set_footprint_limit __malloc_set_footprint_limit
#    define dlmalloc_inspect_all   __malloc_inspect_all
#    define dlindependent_calloc   __independent_calloc
#    define dlindependent_comalloc __independent_comalloc
#    define dlbulk_free            __bulk_free

    /*
     * malloc_usable_size(void* p);
     * 
     * Returns the number of bytes you can actually use in
     * an allocated chunk, which may be more than you requested (although
     * often not) due to alignment and minimum size constraints.
     * You can use this many bytes without worrying about
     * overwriting other allocated objects. This is not a particularly great
     * programming practice. malloc_usable_size can be more useful in
     * debugging and assertions, for example:
     * 
     * p = malloc(n);
     * assert(malloc_usable_size(p) >= 256);
     */
    size_t dlmalloc_usable_size(void *);

#    if MSPACES

    /*
     * mspace is an opaque type representing an independent
     * region of space that supports mspace_malloc, etc.
     */
    typedef void *mspace;

    /*
     * create_mspace creates and returns a new independent space with the
     * given initial capacity, or, if 0, the default granularity size.  It
     * returns null if there is no system memory available to create the
     * space.  If argument locked is non-zero, the space uses a separate
     * lock to control access. The capacity of the space will grow
     * dynamically as needed to service mspace_malloc requests.  You can
     * control the sizes of incremental increases of this space by
     * compiling with a different DEFAULT_GRANULARITY or dynamically
     * setting with mallopt(M_GRANULARITY, value).
     */
    mspace create_mspace(size_t capacity, int locked);

    /*
     * destroy_mspace destroys the given space, and attempts to return all
     * of its memory back to the system, returning the total number of
     * bytes freed. After destruction, the results of access to all memory
     * used by the space become undefined.
     */
    size_t destroy_mspace(mspace msp);

    /*
     * create_mspace_with_base uses the memory supplied as the initial base
     * of a new mspace. Part (less than 128*sizeof(size_t) bytes) of this
     * space is used for bookkeeping, so the capacity must be at least this
     * large. (Otherwise 0 is returned.) When this initial space is
     * exhausted, additional memory will be obtained from the system.
     * Destroying this space will deallocate all additionally allocated
     * space (if possible) but not the initial base.
     */
    mspace create_mspace_with_base(void *base, size_t capacity, int locked);

    /*
     * mspace_track_large_chunks controls whether requests for large chunks
     * are allocated in their own untracked mmapped regions, separate from
     * others in this mspace. By default large chunks are not tracked,
     * which reduces fragmentation. However, such chunks are not
     * necessarily released to the system upon destroy_mspace.  Enabling
     * tracking by setting to true may increase fragmentation, but avoids
     * leakage when relying on destroy_mspace to release all memory
     * allocated using this space.  The function returns the previous
     * setting.
     */
    int mspace_track_large_chunks(mspace msp, int enable);

#        if !NO_MALLINFO
    /*
     * mspace_mallinfo behaves as mallinfo, but reports properties of
     * the given space.
     */
    struct mallinfo mspace_mallinfo(mspace msp);
#        endif                  /* NO_MALLINFO */

    /*
     * An alias for mallopt.
     */
    int mspace_mallopt(int, int);

    /*
     * The following operate identically to their malloc counterparts
     * but operate only for the given mspace argument
     */
    void *mspace_malloc(mspace msp, size_t bytes);
    void mspace_free(mspace msp, void *mem);
    void *mspace_calloc(mspace msp, size_t n_elements, size_t elem_size);
    void *mspace_realloc(mspace msp, void *mem, size_t newsize);
    void *mspace_realloc_in_place(mspace msp, void *mem, size_t newsize);
    void *mspace_memalign(mspace msp, size_t alignment, size_t bytes);
    void **mspace_independent_calloc(mspace msp, size_t n_elements, size_t elem_size, void *chunks[]);
    void **mspace_independent_comalloc(mspace msp, size_t n_elements, size_t sizes[], void *chunks[]);
    size_t mspace_bulk_free(mspace msp, void **, size_t n_elements);
    size_t mspace_usable_size(const void *mem);
    void mspace_malloc_stats(mspace msp);
    int mspace_trim(mspace msp, size_t pad);
    size_t mspace_footprint(mspace msp);
    size_t mspace_max_footprint(mspace msp);
    size_t mspace_footprint_limit(mspace msp);
    size_t mspace_set_footprint_limit(mspace msp, size_t bytes);
    void mspace_inspect_all(mspace msp, void (*handler) (void *, void *, size_t, void *), void *arg);
#    endif                      /* MSPACES */

    extern cell_error mem_error;

      cell_error_decl(no_memory);

    void *dlmalloc(size_t);
    cell_error cell_os_sbrk(cell_uint32 inc, void **ptr);

    static inline void *__morecore(cell_size sz) {
        void *ptr = CELL_NULL;
        cell_error err;

        if((err = cell_os_sbrk(sz, &ptr)) != CELL_NULL) {
            return (void *)(~(size_t) 0);
        }

        return ptr;
    }

    static inline void *memset(void *str, int c, size_t n) {
        char *p = (char *)str;

        for(size_t i = 0; i < n; i++) {
            *p++ = c;
        }

        return str;
    }

    static inline void *memcpy(void *str1, const void *str2, size_t n) {
        char *s1 = (char *)str1;
        const char *s2 = (const char *)str2;

        while(n--)
            *s1++ = *s2++;

        return str1;
    }

#endif /* MALLOC_280_H */
