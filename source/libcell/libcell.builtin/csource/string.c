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

extern cell_size c_strlen(const char *c_str);

cell_string cell_string_c(const char *restrict c_string) {

    cell_string s = {
        .buffer = (cell_byte *) c_string,   // safe
        .len = c_strlen(c_string) + 1
    };

    return s;
}

cell_size cell_string_size(const cell_string s) {
    return s.len + sizeof(s.len);
}

cell_size cell_string_len(const cell_string s) {
    return s.len;
}
