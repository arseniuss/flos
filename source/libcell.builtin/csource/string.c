/* 
 * Builtin library of cell language
 * Copyright (c) 2017, 2018 Armands Arseniuss Skolmeisters
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
#include <cell/memory.h>

extern size_t c_strlen(const byte * c_str);

string string_c(const byte * restrict c_string) {

    string s = {
        .buffer = (byte *) c_string,   // safe
        .len = c_strlen(c_string) + 1
    };

    return s;
}

size_t string_size(const string s) {
    return s.len + sizeof(s.len);
}

size_t string_len(const string s) {
    return s.len;
}

string *string_new(size_t len) {
    return (string *) string_make(sizeof(size_t) + len);
}
