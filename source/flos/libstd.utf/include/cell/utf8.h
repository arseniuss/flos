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

#ifndef __CELL__STD_UTF8_H__
#    define __CELL__STD_UTF8_H__

#    include <cell/type.h>
#    include <cell/string.h>

// module utf8

#    define utf8_max            6 /* maximum bytes per character */
#    define utf8_single         0x80
#    define utf8_error          ((cell_char)-1)

// func isalpha(c char) bool
cell_bool utf8_isalpha(cell_char c);

// func iscntrl(c char) bool
cell_bool utf8_iscntrl(cell_char c);

// func isdigit(c char) bool
cell_bool utf8_isdigit(cell_char c);

// func toint(c char) int
cell_int8 utf8_toint(cell_char c);

// func islower(c char) bool
cell_bool utf8_islower(cell_char c);

// func isspace(c char) bool
cell_bool utf8_isspace(cell_char c);

// func istitle(c char) bool
cell_bool utf8_istitle(cell_char c);

// func isupper(c char) bool
cell_bool utf8_isupper(cell_char c);

// func tolower(c char) char
cell_char utf8_tolower(cell_char c);

// func toupper(c char) char
cell_char utf8_toupper(cell_char c);

// func len(s string) int
cell_size utf8_len(cell_string s);

int utf8_tochar(cell_char * p, const cell_byte * s, cell_size len);

// func fromchar(char ch) ( int, byte[])
int utf8_fromchar(cell_char ch, cell_byte *b, cell_size sz);

cell_int32 utf8_char_len(cell_char ch);




#endif /* __CELL__STD_UTF8_H__ */
