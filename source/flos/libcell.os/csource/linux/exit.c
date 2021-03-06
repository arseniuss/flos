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

#include <cell/string.h>
#include <cell/linux.h>

void cell_os_exit_s(const cell_string msg) {
    cell_linux_sys_write(1, msg.buffer, msg.len);

    cell_linux_sys_exit(msg.len == 0 ? 0 : 1);
}

void cell_os_exit_p(const char *msg) {
    cell_linux_sys_write(1, msg, cell_c_strlen(msg));

    cell_linux_sys_exit((msg == CELL_NULL || *msg == 0) ? 0 : 1);
}
