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

#include <cell/type.h>

cell_size cell_c_strlen(const char *c_str) {
    cell_size size = 0;

    if(c_str) {
        while(*c_str)
            size++, c_str++;
    }

    return size;
}

void *memcpy(void *dest, const void *src, cell_size sz) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    while(sz--)
        *d++ = *s++;

    return (void *)d;
}

void *memset(void *str, int c, cell_size n) {
    char *d = (char *)str;

    while(n--) {
        *d++ = c;
    }

    return str;
}
