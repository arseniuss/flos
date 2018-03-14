#include <cell/array.h>
#include <cell/defs.h>
#include <cell/type.h>

#ifdef NAMESPACE
#undef NAMESPACE
#endif
#define NAMESPACE cell_array
#include <cell/namespace.inc>

size_t __fM4cell5arrayN15array_type_sizePvRui32(type_t ptr)
{
    if(efunc(cell_type, class)(ptr) != TYPE_ARRAY)
        return 0;
    
    struct array_desc* at = 
        (struct array_desc *)efunc(cell_type, desc)(ptr);
    
    return efunc(cell_type, size)(at->of_type) * at->count;
} 

size_t func(array_type_size)(type_t ptr)
        alias("__fM4cell5arrayN15array_type_sizePvRui32");
