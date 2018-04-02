#include <cell/string.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_string
#include <cell/namespace.inc>

size_t func(size) (const struct string s) {
    return s.size;
}

void func(size_calc) (struct string * s) {
    size_t sz;
    const byte *p;

    for(sz = 0, p = s->buffer; *p != '\0'; p++, sz++);

    s->size = sz + 1;
}
