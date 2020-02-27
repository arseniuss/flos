/**
 *   Builtin library for cell language
 *   Copyright (C) 2017 - 2019 Armands Arseniuss Skolmeisters
 *
 *   This library is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this library  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __CELL__ARRAY_H__
#    define __CELL__ARRAY_H__

#    include <cell/builtin.h>
#    include <cell/memory.h>
#    include <cell/type.h>

// module builtin.array

/**
 * Array descriptor
 */
// type array_desc struct {
//      of_type type
//      len     size_type
// }
typedef struct {
    cell_type of_type;
    cell_size count;
} cell_array_desc;

typedef struct {
    cell_size len;
    cell_size cap;
    cell_byte *buffer;
} cell_array;


//#    include <cell/assert.h>
// func make(len, cap size_t) []?
#    define cell_array_make(name, l, c) \
    cell_assert(l <= c); \
    cell_byte * __##name##__buffer = __builtin_alloca(c); \
    cell_array name; \
    name.len = l; name.cap = c; name.buffer = __##name##__buffer;

#endif /* __CELL__ARRAY_H__ */
