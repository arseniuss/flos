/*
 * Standard ASCII encoding library for cell language
 * Copyright (c) 2019 Armands Arseniuss Skolmeisters
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

#ifndef __CELL__STD_ASCII_H__
#    define __CELL__STD_ASCII_H__

#    include <cell/string.h>
#    include <cell/type.h>

// module ascii

// func isalnum(c char) bool
cell_bool cell_ascii_isalnum(cell_char c);

// func isalpha(c char) bool
cell_bool cell_ascii_isalpha(cell_char c);

// func iscntrl(c char) bool
cell_bool cell_ascii_iscntrl(cell_char c);

// func isdigit(c char) bool
cell_bool cell_ascii_isdigit(cell_char c);

// func islower(c char) bool
cell_bool cell_ascii_islower(cell_char c);

// func isspace(c char) bool
cell_bool cell_ascii_isspace(cell_char c);

// func isupper(c char) bool
cell_bool cell_ascii_isupper(cell_char c);

// func tolower(c char) char
cell_char cell_ascii_tolower(cell_char c);

// func toupper(c char) char
cell_char cell_ascii_toupper(cell_char c);

// func isblank(c char) bool
cell_bool cell_ascii_isblank(cell_char c);

// func isxdigit(c char) bool
cell_bool cell_ascii_isxdigit(cell_char c);

// func ispunct(c char) bool
cell_bool cell_ascii_ispunct(cell_char c);

// func isgraph(c char) bool
cell_bool cell_ascii_isgraph(cell_char c);

// func isprint(c char) bool
cell_bool cell_ascii_isprint(cell_char c);

#endif /* __CELL__STD_ASCII_H__ */
