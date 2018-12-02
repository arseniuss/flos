/*
 * Standard UTF-8 encoding library for cell language
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
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

#include "type.h"

/* lookup table for the number of bytes expected in a sequence */
const byte __utfcnt[64] = {
    0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* 1100xxxx */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* 1101xxxx */
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, /* 1110xxxx */
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0, /* 1111xxxx */
};

int __compare1(const void *v1, const void *v2) {
    char c1 = *(char *)v1;
    char c2 = *(char *)v2;

    return c1 - c2;
}

int __compare2(const void *v1, const void *v2) {
    char c = *(char *)v1;
    char *p = (char *)v2;

    return c >= p[0] && c < p[1] ? 0 : c - p[0];
}

void *__bsearch(const void *key, const void *ptr, size_t count, size_t size,
                int (*comp) (const void *, const void *)) {
    void *current;
    size_t lower = 0;
    size_t upper = count;
    size_t index;
    int result;

    if(count == 0 || size == 0)
        return NULL;

    while(lower < upper) {
        index = (lower + upper) / 2;

        current = (void *)(((byte *) ptr) + (index * size));
        result = comp(key, current);

        if(result < 0)
            upper = index;
        else if(result > 0)
            lower = index + 1;
        else
            return current;
    }

    return NULL;
}
