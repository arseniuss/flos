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

#include <cell/error.h>
#include <cell/io.h>
#include <cell/os/file.h>
#include <cell/os/proc.h>

TEST(os_open_test) {
    cell_error err;
    cell_os_file f;

    if((err = cell_os_open(cell_string_c("tests/open.this"), &f)) != CELL_NULL) {
        cell_os_exit(err->string(err));
    }

    cell_io_printf(cell_string_c("os_open OK\n"));
}
