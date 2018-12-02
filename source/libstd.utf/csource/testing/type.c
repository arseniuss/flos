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

#include <cell/string.h>
#include <cell/testing.h>
#include <cell/utf8.h>

TEST(utf8_isalpha) {
    assert(utf8_isalpha('a'));
}

TEST(utf8_len) {
    string str = string_c("こんにちは世界");

    assert_info("str = %s\n", str.buffer);

    size_t sz = utf8_len(str);

    assert_info("sz = %d\n", sz);

    assert(sz == 7);
}
