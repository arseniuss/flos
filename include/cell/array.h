/* 
 * Builtin library of cell language
 * Copyright (c) 2017, 2018 Armands Arseniuss Skolmeisters
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CELL__ARRAY_H__
#    define __CELL__ARRAY_H__

#    include <cell/builtin.h>
#    include <cell/memory.h>
#    include <cell/type.h>
#    include <cell/testing.h>

// module builtin.array

/**
 * Array descriptor
 */
// type array_desc struct {
//      of_type type_t
//      len     size_t
// }
struct array_desc {
    type_t of_type;
    size_t count;
};

typedef struct {
    size_t len;
    byte *buffer;
} array;


// func make(len, cap size_t) []?
#    define array_make(l, c)    ({ assert(l <= c);\
                                array* a = memory_salloc(sizeof(array) + c);\
                                a->len = l; a->cap = c; \
                                a->buffer = ((byte*)a) + sizeof(a); *a;})

#endif /* __CELL__ARRAY_H__ */
