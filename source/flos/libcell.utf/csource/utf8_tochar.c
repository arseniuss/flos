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

#include <cell/utf8.h>

#include "type.h"

// func tochar() char

cell_size cell_utf8_tochar(cell_char * p, const cell_byte * s, cell_size len) {
    cell_byte c, i, m, n, x;
    char r;

    if(len == 0)                       /* can't even look at s[0] */
        return 0;

    c = *s++;

    if(!(c & 0200))                    /* basic byte */
        return (*p = c, 1);

    if(!(c & 0100))                    /* continuation byte */
        return (*p = cell_utf8_error, 1);

    n = __utfcnt[c & 077];

    if(n == 0)                         /* illegal byte */
        return (*p = cell_utf8_error, 1);

    if(len == 1)                       /* reached len limit */
        return 0;

    if((*s & 0300) != 0200)            /* not a continuation byte */
        return (*p = cell_utf8_error, 1);

    x = 0377 >> n;
    r = c & x;

    r = (r << 6) | (*s++ & 077);

    if(r <= x)                         /* overlong sequence */
        return (*p = cell_utf8_error, 2);

    m = (len < n) ? len : n;

    for(i = 2; i < m; i++) {
        if((*s & 0300) != 0200)        /* not a continuation byte */
            return (*p = cell_utf8_error, i);

        r = (r << 6) | (*s++ & 077);
    }

    if(i < n)                          /* must have reached len limit */
        return 0;

    if(!__isvalid(r))
        return (*p = cell_utf8_error, i);

    return (*p = r, i);

}
