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

#include <cell/testing.h>
#include <cell/defs.h>

int defer_var = 1;

TEST(defer_test) {

    {
        defer {
            defer_var += 1;
        };
        defer {
            defer_var *= 3;
        };
    }
    /*
     * Defer blocks should execute in FOFI order
     * defer_var = (1 * 3) + 1 = 4 not (1 + 1) * 3 = 6
     */

    assert(defer_var == 4);
}
