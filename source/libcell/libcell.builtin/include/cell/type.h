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

#pragma once

#include <cell/builtin.h>

// module builtin

/**
 * Types in cell refection is defined as pointers where 8 lower bits describe
 * type but higher are used as a pointer to aligned structure of type (if there
 * is any).
 * 
 * Pointer:
 * 31                         7
 * +--------+--------+--------+--------+
 * |                          |        |
 * +--------+--------+--------+--------+
 */

/**
 * Lower 3 bits describe bit size
 */
#define TYPE_BIT8        1             // 001
#define TYPE_BIT16       2             // 010
#define TYPE_BIT32       3             // 011
#define TYPE_BIT64       4             // 100
#define TYPE_BIT128      5             // 101
#define TYPE_BIT_RES1    6             // 110
#define TYPE_BIT_RES2

#define TYPE_BIT_MASK    7             // 111
#define TYPE_BIT_BITS    3

/**
 * Upper 5 bits describe class
 */

#define TYPE_UINT        1             // 0001
#define TYPE_SINT        2             // 0010
#define TYPE_FLOAT       3             // 0011
#define TYPE_IFLOAT      4             // 0100
#define TYPE_CFLOAT      5             // 0101

#define TYPE_PTR         8             // 1000


#define TYPE_ARRAY       9             // 1001
#define TYPE_SLICE      10             // 1010

#define TYPE_FUNC       11             // 1011
#define TYPE_STRUCT     12             // 1100
#define TYPE_INTERFACE  13             // 1101
#define TYPE_CLASS      14             // 1110

#define TYPE_CLASS_MASK 0xF

#define TYPE_MASK      0xFF

#define UINT_TYPE(bits)   (TYPE_UINT & (bits & TYPE_BIT_MASK))
#define SINT_TYPE(bits)   (TYPE_SINT & (bits & TYPE_BIT_MASK))
#define FLOAT_TYPE(bits)  (TYPE_FLOAT & (bits & TYPE_BIT_MASK))
// TODO: continue

#define PTR_TYPE(target_type) ((target_type & ~((uintptr_t)TYPE_MASK)) & TYPE_PTR)
// TODO: continue

/**
 * This structure define pointer to type.
 * Lower 8 bits describe type so target structure's pointer should be aligned
 * 8 bits.
 */
typedef cell_uintptr cell_type;

//// func (ptr type_t) desc() *void
//void *func(desc) (type_t ptr);
//
//// func (ptr type_t) class() uint8
//uint8 func(class) (type_t ptr);
//
//// func (ptr type_t) bits() uint8
//uint8 func(bits) (type_t ptr);
//
//// func (ptr type_t) iscomplex() bool
//bool func(iscomplex) (type_t ptr);
//
//struct type_info {
//    void *desc;
//    uint8 bits;
//    uint8 cls;
//};
//
//struct type_info func(get_type_info) (type_t ptr);
//
//size_t func(size) (type_t ptr);
