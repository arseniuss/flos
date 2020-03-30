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
#include <cell/os/error.h>
#include <cell/os/file.h>
#include <cell/linux.h>

#include "internal.h"

cell_error cell_os_write_a(cell_os_file __this, const cell_slice_type * arg1) {
    if(__this == CELL_NULL)
        return __this_error;

    cell_ssize res = cell_linux_sys_write(__this->fd, arg1->buf, arg1->len);
    if(res < 0)
        return cell_os_error[cell_linux_sys_errno];

    return CELL_NULL;
}

cell_error cell_os_write_s(cell_os_file __this, const cell_string arg1) {
    if(__this == CELL_NULL)
        return __this_error;

    cell_ssize res = cell_linux_sys_write(__this->fd, arg1.buffer, arg1.len);
    if(res < 0)
        return cell_os_error[cell_linux_sys_errno];

    return CELL_NULL;
}
