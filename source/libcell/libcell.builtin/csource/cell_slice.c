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

#include <cell/string.h>
#include <cell/slice.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE cell_slice
#include <cell/namespace.h>

size_t func(slice_type_size) (type_t ptr) {
    if(efunc(cell_type, class) (ptr) != TYPE_SLICE)
        return 0;

    struct slice_desc *st = (struct slice_desc *)efunc(cell_type, desc) (ptr);

    return efunc(cell_type, size) (st->of_type);
}

size_t func(slice_size) (type_t slice_type, const struct slice * s) {
    return s->count * efunc(cell_type, size) (slice_type);
}

uint32 func(slice_cap) (const struct slice * s) {
    return s->cap;
}

struct slice_at_return func(slice_at) (type_t t, const struct slice s,
                                       uint32 index) {
    struct slice_at_return r;

    if(index >= s.count) {
        string error;

        r.data = NULL;

        error.buffer = (const byte *)"index out of bounds";
        efunc(cell_string, size_calc) (&error);

        r.error = &error;

        return r;
    } else {
        r.data = s.data + (index * func(slice_type_size) (t));
        r.error = NULL;
    }

    return r;
}
