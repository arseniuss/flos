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

#ifndef __CELL__BUILTINT_H__
#    define __CELL__BUILTINT_H__

// module builtin

/**
 * Bool type
 */

#    ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ bool;
#    else
#        error __UINT8_TYPE__ not defined!
#    endif

/**
 * Integer types
 */

#    ifdef char
#        define TMP_char char
#        undef char
#    endif
typedef char c_char;
#    ifdef TMP_char
#        define char TMP_char
#        undef TMP_char
#    endif

#    ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
typedef c_char byte;
#    else
#        error __UINT8_TYPE__ not defined!
#    endif

#    ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#    else
#        error __UINT16_TYPE__ not defined!
#    endif

#    ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#    else
#        error __UINT32_TYPE__ not defined!
#    endif

#    ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#    else
#        error __UINT32_TYPE__ not defined!
#    endif

#    ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
#    else
#        error __INT8_TYPE__ not defined!
#    endif

#    ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
#    else
#        error __INT16_TYPE__ not defined!
#    endif

#    ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
#    else
#        error __INT32_TYPE__ not defined!
#    endif

#    ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
#    else
#        error __INT64_TYPE__ not defined!
#    endif

/**
 * Pointer types
 */

#    ifdef __INTPTR_TYPE__
typedef __INTPTR_TYPE__ intptr_t;
#    else
#        error __INTPTR_TYPE__ not defined!
#    endif

#    ifdef __UINTPTR_TYPE__
typedef __UINTPTR_TYPE__ uintptr_t;
#    else
#        error __UINTPTR_TYPE__ not defined!
#    endif

#    ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __PTRDIFF_TYPE__ ssize_t;
#    else
#        error __PTRDIFF_TYPE__ not defined!
#    endif

/**
 * Other number types
 */

#    ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#    else
#        error __SIZE_TYPE__ not defined!
#    endif

#    define NULL ((void *)0)

#endif /* __CELL__BUILTINT_H__ */
