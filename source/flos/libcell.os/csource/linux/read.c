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

#include <cell/os/error.h>
#include <cell/os/file.h>
#include <cell/linux.h>

#include "internal.h"

cell_error cell_os_read(cell_os_file __this, cell_slice_type * ret1) {
    if(!__this)
        return __this_error;

    if(ret1->cap - ret1->len == 0)
        return __ret1_error;           // empty buffer

    cell_ssize sz;

    if((sz = cell_linux_sys_read(__this->fd, &ret1->buf[ret1->len], ret1->cap - ret1->len)) == -1) {
        return cell_os_error[cell_linux_sys_errno];
    }

    ret1->len += sz;

    return CELL_NULL;
}
