/* 
 * This file is part of the libcell distribution
 * Copyright (c) 2017 Armands Arseniuss Skolmeisters
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
#pragma once

// module cell.string

#include <cell/builtin.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_string
#include <cell/namespace.h>

// type char int32
#ifndef char
#    define char int32
//#warning `char` is defined as 32bit integer!
#endif

// type string !struct {
// private:
//      size int32
//      buffer *byte
// }
typedef struct {
    size_t size;
    const byte *buffer;
} string;

// func (s string) size() size_t {
//      return s.size
// }
size_t func(size) (const string s);

void func(size_calc) (string * s);

// func +(s1, s2 string) string @unsafe {
//      var size = s1.size + s2.size -1 // '\0'
//      var buffer = new [s1.size]byte // *[?]byte
//      
//      memcpy(buffer, s1.buffer, s1.size) // func memcpy(target, source *, size size_t)
//      memcpy(buffer + s1.size, s2.buffer, s2.size)
//      
//      return (string){ size, buffer }
//  }
