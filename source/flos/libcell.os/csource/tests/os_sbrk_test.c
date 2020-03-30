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

#include <cell/io.h>
#include <cell/os/mem.h>
#include <cell/os/proc.h>
#include <cell/error.h>

TEST(os_sbrk_test) {
    void *p1, *p2, *p3 = CELL_NULL;
    cell_error err;

    if((err = cell_os_sbrk(0, &p1)) != CELL_NULL) {
        cell_os_exit(err->string(err));
    } else {
        cell_io_printf_s(cell_string_c("os_sbrk(0) returned %#x\n"), p1);
    }

    if((err = cell_os_sbrk(100, &p2)) != CELL_NULL) {
        cell_os_exit(err->string(err));
        return;
    }

    cell_io_printf_s(cell_string_c("os_sbrk(100) returned %#x\n"), p2);

    if((err = cell_os_sbrk(100, &p3)) != CELL_NULL) {
        cell_os_exit(err->string(err));
        return;
    }

    if(p2 + 100 != p3) {
        cell_os_exit(cell_string_c("error"));
    } else {
        cell_io_printf_s(cell_string_c("os_sbrk(100) returned %#x\n"), p3);
    }

    cell_io_printf_s(cell_string_c("os_sbrk OK\n"));
}
