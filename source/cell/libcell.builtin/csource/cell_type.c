#include <cell/slice.h>
#include <cell/array.h>

#include <cell/type.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_type
#include <cell/namespace.inc>

void *func(desc) (type_t ptr) {
    return (void *)(ptr & ~TYPE_MASK);
}

uint8 func(class) (type_t ptr) {
    return (ptr >> TYPE_BIT_BITS) & TYPE_CLASS_MASK;
}

uint8 func(bits) (type_t ptr) {
    return ptr & TYPE_BIT_MASK;
}

bool func(iscomplex) (type_t ptr) {
    return ptr > TYPE_MASK;
}

struct type_info func(get_type_info) (type_t ptr) {
    struct type_info td;

    td.cls = func(class) (ptr);

    if(func(iscomplex) (ptr)) {
        td.desc = func(desc) (ptr);
    } else {
        td.bits = func(bits) (ptr);
    }

    return td;
}

size_t func(size) (type_t ptr) {
    uint8 cls = func(class) (ptr);

    switch (cls) {
        case TYPE_SINT:
        case TYPE_UINT:
        case TYPE_FLOAT:
        case TYPE_IFLOAT:
            return 1 << (ptr & TYPE_BIT_MASK);
        case TYPE_CFLOAT:
            return (1 << (ptr & TYPE_BIT_MASK)) * 2;
        case TYPE_PTR:
            return sizeof(void *);
        case TYPE_ARRAY:
            return efunc(cell_array, type_size) (ptr);
        case TYPE_SLICE:
            return efunc(cell_slice, slice_type_size) (ptr);
            // TODO: continue
    }

    return 0;
}
