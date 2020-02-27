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

#include <cell/type.h>
#include <cell/string.h>

#include "type.h"

#define LEN(x)          (sizeof(x)/sizeof*(x))

// module utf8

// func (c char) <ISCHAR>() bool

cell_bool ISCHAR(cell_char c) {
    cell_char *match;

#ifdef RANGES
    if((match = __bsearch(&c, RANGES, LEN(RANGES), sizeof *RANGES, __compare2)))
        return 1;
#endif

#ifdef LACES1
    if((match = __bsearch(&c, LACES1, LEN(LACES1), sizeof *LACES1, __compare2)))
        return !((c - match[0]) % 2);
#endif

#ifdef LACES2
    if((match = __bsearch(&c, LACES2, LEN(LACES2), sizeof *LACES2, __compare2)))
        return !((c - match[0]) % 2);
#endif

#ifdef SINGLES
    if((match =
        __bsearch(&c, SINGLES, LEN(SINGLES), sizeof *SINGLES, __compare1)))
        return 1;
#endif

    return 0;
}

#ifdef TOCHAR

// func (c char) <TOCHAR>() char

cell_char TOCHAR(cell_char c) {
    cell_char *match;

#    ifdef RANGES
    if((match = __bsearch(&c, RANGES, LEN(RANGES), sizeof *RANGES, __compare2)))
        return match[2] + (c - match[0]);
#    endif
#    ifdef LACES1
    if((match = __bsearch(&c, LACES1, LEN(LACES1), sizeof *LACES1, __compare2)))
        return ((c - match[0]) % 2) ? c : c + 1;
#    endif
#    ifdef LACES2
    if((match = __bsearch(&c, LACES2, LEN(LACES2), sizeof *LACES2, __compare2)))
        return ((c - match[0]) % 2) ? c : c - 1;
#    endif
#    ifdef SINGLES
    if((match =
        __bsearch(&c, SINGLES, LEN(SINGLES), sizeof *SINGLES, __compare1)))
        return match[1];
#    endif

    return c;
}

#endif

#if defined(TOINT) && defined(RANGES)
cell_int8 TOINT(cell_char c) {
    cell_char *match;
    
    if((match = __bsearch(&c, RANGES, LEN(RANGES), sizeof *RANGES, __compare2)))
        return c - match[0];
    
    return -1;
}
#endif /* TOINT */
