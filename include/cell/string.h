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
#ifndef __CELL__STRING_H__
#    define __CELL__STRING_H__

// module builtin.string

#    include <cell/array.h>
#    include <cell/builtin.h>
#    include <cell/memory.h>

#    ifdef char
#        error char is already defined!
#    endif

// type int32 char
#    define char        int32_t

// type string !struct {
// private:
//      size uint32
//      buffer *byte
// }

typedef struct {
    size_t len;
    byte* buffer;
} string;


string string_c(const byte * restrict c_string);

/**
 * Function returns full size of string in bytes
 * @param s string
 * @return size of string in bytes
 */
// func (s string) size() size_t
size_t string_size(const string s);

/**
 * Function returns length of string in bytes
 * @param s string
 * @return length of string in bytes
 */
// func (s string) len() size_t
size_t string_len(const string s);

#    ifdef HAS_MEM_ALLOC

// func +(s1, s2 string) string
const string __string_add(const string s1, const string s2);

#    endif

/**
 * Allocates string from stack memory
 * @param len string buffer len
 * @return pointer to string
 */
// func (string s) new(len size_t) *string
#    define string_make(l)        ({string* __s = memory_salloc(sizeof(size_t) + (l)); \
                                ((string *)__s)->len = l; ((string*)__s)->buffer = ((byte *)__s) + sizeof(size_t); __s;  })

#endif /* __CELL__STRING_H__ */
