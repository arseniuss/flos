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

#ifndef __CELL__STRING_H__
#    define __CELL__STRING_H__

// module builtin.string

#    include <cell/builtin.h>
#    include <cell/memory.h>
#    include <cell/array.h>

#    ifdef char
#        error char is already defined!
#    endif

// type int32 char
#    define cell_char        cell_int32

// type string !struct {
// private:
//      size uint32
//      buffer *byte
// }

typedef struct {
    cell_size len;
    cell_byte *buffer;
} cell_string;

// func (str *string) init()
static inline void cell_string_init(cell_string * str) {
    str->len = 0;
    str->buffer = CELL_NULL;
}


cell_string cell_string_c(const char *restrict c_string);
cell_string cell_string_a(cell_array_byte a);

cell_size cell_c_strlen(const char *);

/**
 * Function returns full size of string in bytes
 * @param s string
 * @return size of string in bytes
 */
// func (s string) size() size
cell_size cell_string_size(const cell_string s);

/**
 * Function returns length of string in bytes
 * @param s string
 * @return length of string in bytes
 */
// func (s string) len() size_t
cell_size cell_string_len(const cell_string s);

// func (s1, s2 string) eq() bool
cell_bool cell_string_eq(const cell_string * s1, const cell_string * s2);

// func (str string) copy() string
void cell_string_copy(const cell_string * str, cell_string * ret);

#endif /* __CELL__STRING_H__ */
