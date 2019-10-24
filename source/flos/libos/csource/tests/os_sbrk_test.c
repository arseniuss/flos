/**
 *  OS layer library
 *  Copyright (C) 2019 Armands Arseniuss Skolmeisters
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cell/std/io.h>
#include <cell/os.h>

TEST(os_sbrk_test) {
    void *p1, *p2, *p3 = CELL_NULL;
    cell_error *err;

    if((err = os_sbrk(0, &p1)) != CELL_NULL) {
        os_exit(err->string());
    } else {
        io_printf(cell_string_c("os_sbrk(0) returned %#x\n"), p1);
    }

    if((err = os_sbrk(100, &p2)) != CELL_NULL) {
        os_exit(err->string());
    } else if(p1 + 100 != p2) {
        os_exit(cell_string_c("error"));
    } else {
        io_printf(cell_string_c("os_sbrk(100) returned %#x\n"), p2);
    }

    if((err = os_sbrk(100, &p3)) != CELL_NULL) {
        os_exit(err->string());
    } else if(p2 + 100 != p3) {
        os_exit(cell_string_c("error"));
    } else {
        io_printf(cell_string_c("os_sbrk(100) returned %#x\n"), p3);
    }
}
