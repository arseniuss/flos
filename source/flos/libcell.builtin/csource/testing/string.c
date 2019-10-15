/**
 *   Builtin library for cell language
 *   Copyright (C) 2019 Armands Arseniuss Skolmeisters
 *
 *   This library is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this library  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cell/string.h>
#include <cell/testing.h>

#define TEST_STR1             "TESTING "
#define TEST_STR2             "STRING!"
#define TEST_STR              TEST_STR1 TEST_STR2
#define TEST_STR_SIZE         sizeof(TEST_STR)

TEST(string_c) {

    const byte s[] = TEST_STR;

    string str = string_c(s);


    assert(str.len == TEST_STR_SIZE);
    assert(str.buffer == &s[0]);
}

TEST(string_size) {
    string s = string_c(TEST_STR);

    assert(string_size(s) == TEST_STR_SIZE + sizeof(size_t));

}

TEST(string_len) {
    string s = string_c(TEST_STR);

    assert(string_len(s) == TEST_STR_SIZE);
}

TEST(string_make) {
    string *s = string_make(TEST_STR_SIZE);

    assert(s->len == TEST_STR_SIZE);
    assert(s->buffer != NULL);
}
