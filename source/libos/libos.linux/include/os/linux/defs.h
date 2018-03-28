/* 
 * This file is part of the libos distribution for cell standard library
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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

#define XCONCAT(x, y)    x ## y
#define CONCAT(x, y)    XCONCAT(x, y)

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#else
#error __SIZE_TYPE__ is not defined!
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __PTRDIFF_TYPE__ ssize_t;
#else
#error __PTRDIFF_TYPE__ is not defined!
#endif

typedef int pid_t;
struct pt_regs {
    long reg[8];
};
