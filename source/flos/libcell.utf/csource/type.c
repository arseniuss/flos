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

#include <cell/builtin.h>
#include <cell/string.h>


#include "type.h"

/* lookup table for the number of bytes expected in a sequence */
const cell_byte __utfcnt[64] = {
    0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* 1100xxxx */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* 1101xxxx */
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, /* 1110xxxx */
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0, /* 1111xxxx */
};

int __isvalid(cell_char r) {
    if(r < 0)
        return 0;                      /* negative value */

    if(r >= 0xD800 && r <= 0xDFFF)
        return 0;                      /* surrogate pair range */

    if(r >= 0xFDD0 && r <= 0xFDEF)
        return 0;                      /* non-character range */

    if((r & 0xFFFE) == 0xFFFE)
        return 0;                      /* non-character at end of plane */

    if(r > 0x10FFFF)
        return 0;                      /* too large, thanks to UTF-16 */

    return 1;
}

int __compare1(const void *v1, const void *v2) {
    cell_char c1 = *(cell_char *) v1;
    cell_char c2 = *(cell_char *) v2;

    return c1 - c2;
}

int __compare2(const void *v1, const void *v2) {
    cell_char c = *(cell_char *) v1;
    cell_char *p = (cell_char *) v2;

    return c >= p[0] && c <= p[1] ? 0 : c - p[0];
}

void *__bsearch(const void *key, const void *ptr, cell_size count,
                cell_size size, int (*comp)(const void *, const void *)) {
    void *current;
    cell_size lower = 0;
    cell_size upper = count;
    cell_size index;
    int result;

    if(count == 0 || size == 0)
        return CELL_NULL;

    while(lower < upper) {
        index = (lower + upper) / 2;

        current = (void *)(((cell_byte *) ptr) + (index * size));
        result = comp(key, current);

        if(result < 0)
            upper = index;
        else if(result > 0)
            lower = index + 1;
        else
            return current;
    }

    return CELL_NULL;
}
