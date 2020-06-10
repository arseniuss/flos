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

cell_int32 cell_utf8_char_len(cell_char ch) {
    if(ch <= 0x7F)
        return 1;
    else if(ch <= 0x07FF)
        return 2;
    else if(ch <= 0xD7FF)
        return 3;
    else if(ch <= 0xDFFF)
        return 0;                      /* surrogate character */
    else if(ch <= 0xFFFD)
        return 3;
    else if(ch <= 0xFFFF)
        return 0;                      /* illegal character */
    else if(ch <= 0x10FFFF)
        return 4;
    else
        return 0;                      /* too large character */
}
