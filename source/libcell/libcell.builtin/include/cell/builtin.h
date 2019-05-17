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
typedef __UINT8_TYPE__ cell_bool;
#    else
#        error __UINT8_TYPE__ not defined!
#    endif

/**
 * Integer types
 */

typedef char cell_c_char;

#    ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ cell_uint8;
typedef char cell_byte;
#    else
#        error __UINT8_TYPE__ not defined!
#    endif

#    ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ cell_uint16;
#    else
#        error __UINT16_TYPE__ not defined!
#    endif

#    ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ cell_uint32;
#    else
#        error __UINT32_TYPE__ not defined!
#    endif

#    ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ cell_uint64;
#    else
#        error __UINT32_TYPE__ not defined!
#    endif

#    ifdef __INT8_TYPE__
typedef __INT8_TYPE__ cell_int8;
#    else
#        error __INT8_TYPE__ not defined!
#    endif

#    ifdef __INT16_TYPE__
typedef __INT16_TYPE__ cell_int16;
#    else
#        error __INT16_TYPE__ not defined!
#    endif

#    ifdef __INT32_TYPE__
typedef __INT32_TYPE__ cell_int32;
#    else
#        error __INT32_TYPE__ not defined!
#    endif

#    ifdef __INT64_TYPE__
typedef __INT64_TYPE__ cell_int64;
#    else
#        error __INT64_TYPE__ not defined!
#    endif

/**
 * Pointer types
 */

#    ifdef __INTPTR_TYPE__
typedef __INTPTR_TYPE__ cell_intptr;
#    else
#        error __INTPTR_TYPE__ not defined!
#    endif

#    ifdef __UINTPTR_TYPE__
typedef __UINTPTR_TYPE__ cell_uintptr;
#    else
#        error __UINTPTR_TYPE__ not defined!
#    endif

#    ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ cell_ptrdiff;
typedef __PTRDIFF_TYPE__ cell_ssize;
#    else
#        error __PTRDIFF_TYPE__ not defined!
#    endif

/**
 * Other number types
 */

#    ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ cell_size;
#    else
#        error __SIZE_TYPE__ not defined!
#    endif

#    define CELL_NULL ((void *)0)



#endif /* __CELL__BUILTINT_H__ */
