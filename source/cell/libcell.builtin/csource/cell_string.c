#include <cell/string.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_string
#include <cell/namespace.h>

size_t func(size) (const string s) {
    return s.size;
}

void func(size_calc) (string * s) {
    size_t sz;
    const byte *p;

    for(sz = 0, p = s->buffer; *p != '\0'; p++, sz++);

    s->size = sz + 1;
}
