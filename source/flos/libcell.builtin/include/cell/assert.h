/**
 *   Builtin library for cell language
 *   Copyright (C) 2017-2019 Armands Arseniuss Skolmeisters
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

#ifndef __CELL__ASSERT_H__
#    define __CELL__ASSERT_H__

#    include <cell/string.h>

void cell_os_exit_s(cell_string str);

#    define cell_assert(x)      do { if(!(x)) cell_os_exit_s(cell_string_c("Assertation error: " #x)); } while(0)

#    define cell_static_assert(x, msg) typedef char static_assertion_##msg[(x)?1:-1]

#endif /* !__CELL__ASSERT_H__ */
