/**
 *   Builtin library for cell language
 *   Copyright (C) 2019 Armands Arseniuss Skolmeisters
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

#include <cell/error.h>
#include <cell/mem.h>
#include <cell/slice.h>
#include <cell/string.h>

extern cell_size cell_c_strlen(const char *c_str);

cell_string cell_string_c(const char *restrict c_string) {

    cell_string s = {
        .buffer = (cell_byte *) c_string,   // safe
        .len = cell_c_strlen(c_string) + 1
    };

    return s;
}

cell_string cell_string_a(cell_array_byte a) {
    return (cell_string) {
    .buffer = a.buf,.len = a.len};
}

cell_size cell_string_size(const cell_string s) {
    return s.len + sizeof(s.len);
}

cell_size cell_string_len(const cell_string s) {
    return s.len;
}

static cell_bool __eq(void *b1, void *b2, cell_size sz) {
    const char *s1 = b1;
    const char *s2 = b2;

    while(sz--)
        if(*s1++ != *s2++)
            return 0;

    return 1;
}

static cell_bool __eq2(const cell_byte * b1, const cell_byte * s1, cell_size sz) {
    while(sz--) {
        if(*b1 == 0 || *s1 == 0)
            return 0;
        if(*b1++ != *s1++)
            return 0;
    }

    if(*s1 != 0)
        return 0;

    return 1;
}

cell_bool cell_string_eq_ss(const cell_string * s1, const cell_string * s2) {
    return s1 != CELL_NULL && s2 != CELL_NULL && s1->len == s2->len && __eq(s1->buffer, s2->buffer, s1->len);
}

cell_bool cell_string_eq_spb(const cell_string * s1, const char *s2) {
    return s1 != CELL_NULL && s2 != CELL_NULL && __eq2(s1->buffer, s2, s1->len);
}

cell_bool cell_string_eq_pbs(const char *s1, const cell_string * s2) {
    return s1 != CELL_NULL && s2 != CELL_NULL && __eq2(s2->buffer, s1, s2->len);
}

cell_bool cell_string_eq_pbpb(const char *s1, const char *s2) {
    while(*s1 && s2)
        if(*s1++ != *s2++)
            return 0;

    return 1;
}

cell_error cell_string_set(cell_string * str, cell_slice_type slice) {
    cell_error err;

    cell_byte *b;
    if((err = cell_mem_alloc(slice.len, (void **)&b)) != CELL_NULL)
        return err;

    return CELL_NULL;
}
