/**
 *   Builtin library for cell language
 *   Copyright (C) 2020 Armands Arseniuss Skolmeisters
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

#include <cell/slice.h>
#include <cell/mem.h>

cell_error __cell_slice_append(cell_slice_type * s, cell_size elem_size, void *value, cell_slice_type * ret) {
    cell_error err;

    if(s->cap <= 0 || s->len == s->cap) {
        cell_size new_size = s->cap + (s->cap * 2) + 1;

        if(s == ret) {
            if((err = cell_mem_realloc(new_size * elem_size, (void **)&ret->buf)) != CELL_NULL)
                return err;
        } else {
            void *buf;

            if((err = cell_mem_alloc(new_size * elem_size, &buf)) != CELL_NULL)
                return err;

            ret->buf = (cell_byte *) buf;
            __builtin_memcpy(ret->buf, s->buf, s->len * elem_size);
        }

        ret->cap = new_size;
        ret->len = s->len;
    }

    __builtin_memcpy(&s->buf[s->len * elem_size], value, elem_size);
    s->len++;

    __builtin_memcpy(ret, s, sizeof(cell_slice_type));

    return CELL_NULL;
}
