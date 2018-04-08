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

#include <cell/builtin.h>
#include <cell/type.h>

// module cell.array

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_array
#include <cell/namespace.h>

struct array_desc {
    type_t of_type;
    size_t count;
};

// func (ptr type_t)type_size() size_t
extern size_t func(type_size) (type_t ptr);
