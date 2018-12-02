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

// func isalpha(c char) bool
bool utf8_isalpha(char c);

// func iscntrl(c char) bool
bool utf8_iscntrl(char c);

// func isdigit(c char) bool
bool utf8_isdigit(char c);

// func islower(c char) bool
bool utf8_islower(char c);

// func issapce(c char) bool
bool utf8_isspace(char c);

// func istitle(c char) bool
bool utf8_istitle(char c);

// func isupper(c char) bool
bool utf8_isupper(char c);

// func tolower(c char) char
char utf8_tolower(char c);

// func toupper(c char) char
char utf8_toupper(char c);

// func len(s string) int
size_t utf8_len(string s);


#endif /* __CELL__STD_UTF8_H__ */
