/* 
 * Manual memory management library for cell language
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

#include <cell/mem/string.h>
#include <cell/mem.h>

cell_error cell_string_copy(cell_string * str, const cell_slice_type * slice, cell_size sz) {
    cell_error err;

    if((err = cell_mem_alloc(sz, (void **)&str->buffer))) {
        return err;
    }

    __builtin_memcpy(str->buffer, slice->buf, sz);
    str->len = sz;

    return CELL_NULL;
}

cell_error cell_string_copy_s(cell_string * s1, const cell_string * s2) {
    cell_error err;

    if((err = cell_mem_alloc(s2->len, (void **)&s1->buffer))) {
        return err;
    }

    __builtin_memcpy(s1->buffer, s2->buffer, s2->len);
    s1->len = s2->len;

    return CELL_NULL;
}
