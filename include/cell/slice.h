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

#include <cell/type.h>

// module cell.slice

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_slice
#include <cell/namespace.h>

struct slice {
    void *data;
    int32 count;
    int32 cap;
};

struct slice_desc {
    type_t of_type;
};

size_t func(slice_type_size) (type_t ptr);

/**
 * Size of slice data
 * @param slice_type slice describing type
 * @param s
 * @return 
 */
// func (s []?) size() size_t
size_t func(slice_size) (type_t slice_type, const struct slice * s);

// func (s []?) cap() uint32
uint32 func(slice_cap) (const struct slice * s);

struct slice_at_return {
    void *data;
    string *error;
};

// func (s []?) at( index uint32) ?
struct slice_at_return func(slice_at) (type_t t, const struct slice s,
                                       uint32 index);
