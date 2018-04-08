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

// module cell.builtin

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_builtin
#include <cell/namespace.h>

#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8;
#else
#    error __UINT8_TYPE__ not defined!
#endif

#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16;
#else
#    error __UINT16_TYPE__ not defined!
#endif

#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32;
#else
#    error __UINT32_TYPE__ not defined!
#endif

#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64;
#else
#    error __UINT32_TYPE__ not defined!
#endif

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8;
#else
#    error __INT8_TYPE__ not defined!
#endif

#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16;
#else
#    error __INT16_TYPE__ not defined!
#endif

#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32;
#else
#    error __INT32_TYPE__ not defined!
#endif

#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64;
#else
#    error __INT64_TYPE__ not defined!
#endif

typedef uint8 bool;
typedef uint8 byte;
typedef __SIZE_TYPE__ size_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

#define NULL ((void *)0)

// func (_ int) size() size_t { return 4; }

#include <cell/string.h>

typedef struct {
    struct string* (*string)(void);
} error;