/**
 *  Linux layer library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
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

#include <cell/os/linux.h>
#include <cell/std/fmt.h>
#include <cell/std/io.h>
#include <cell/assert.h>

TEST(os_sbrk_test) {
    cell_uint64 ret1 = os_linux_sys_brk(CELL_NULL);

    io_printf(cell_string_c("os.linux.sys.brk(null) returned 0x%llX\n"), ret1);

    cell_uint64 ret2 = os_linux_sys_brk(CELL_NULL);

    io_printf(cell_string_c("os.linux.sys.brk(null) returned 0x%llX\n"), ret2);

    cell_uint64 ret3 = os_linux_sys_brk(ret2 + 100);

    io_printf(cell_string_c("os.linux.sys.brk(ret + 100) returned 0x%llX\n"), ret3);

    cell_assert(ret2 + 100 == ret3);

    io_printf(cell_string_c("OK"));
}
