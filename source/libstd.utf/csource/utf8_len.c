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

// module utf8

// func len(s string) uint

size_t utf8_len(string s) {
    uint8_t c, i, m, n, x;
    const byte *p;
    size_t k;
    char r;

    for(k = 0; *(p = s.buffer) != '\0'; s.len -= s.buffer - p, k++) {
        if(s.len == 0)                 /* can't even look at s[0] */
            return k;

        c = *s.buffer++;

        if((c & 0300) != 0300)         /* not a leading byte */
            continue;

        n = __utfcnt[c & 077];

        if(n == 0)                     /* illegal byte */
            continue;

        if(s.len == 1)                 /* reached len limit */
            return k;

        if((*s.buffer & 0300) != 0200) /* not a continuation byte */
            continue;

        x = 0377 >> n;
        r = c & x;

        r = (r << 6) | (*s.buffer++ & 077);

        if(r <= x)                     /* overlong sequence */
            continue;

        m = (s.len < n) ? s.len : n;

        for(i = 2; i < m; i++) {
            if((*s.buffer & 0300) != 0200)  /* not a continuation byte */
                break;

            s.buffer++;
        }

        if(i < m)                      /* broke out of loop early */
            continue;

        if(i < n)                      /* must have reached len limit */
            return k;
    }

    return k;
}
