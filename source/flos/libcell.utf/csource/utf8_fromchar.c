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

int cell_utf8_fromchar(cell_char ch, cell_byte *b, cell_size sz) {
    cell_int32 len = cell_utf8_char_len(ch);
    
    if(len >= sz)
        return 0; 
    
    switch(cell_utf8_char_len(ch)) {
    case 1: /* 0b0xxxxxxx */
        *(b++) = ch;
        return 1;
    case 2:
        *(b++)= 0xC0 | ((ch & 0x0007C0) >> 6); /* 0b110xxxxx */
        *(b++)= 0x80 | (ch & 0x00003F); /* 0b10xxxxxx */
        return 2;
    case 3:
        *(b++) = 0xE0 | ((ch & 0x00F000) >> 12); /* 0b1110xxxx */
        *(b++) = 0x80 | ((ch & 0x000FC0) >> 6); /* 0b10xxxxxx */
        *(b++) = 0x80 | (ch & 0x00003F ); /* 0b10xxxxxx */
        return 3;
    case 4:
        *(b++)= 0xF0 | ((ch & 0x1C0000) >> 18); /* 0b11110xxx */
        *(b++) = 0x80 | ((ch & 0x03F000) >> 12); /* 0b10xxxxxx */
        *(b++) = 0x80 | ((ch & 0x000FC0) >> 6); /* 0b10xxxxxx */
        *(b++) = 0x80 | (ch & 0x00003F);
        return 4;
    default:
        return 0;
    }
}


