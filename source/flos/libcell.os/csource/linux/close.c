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
#include <cell/os/linux.h>

#include "internal.h"

cell_error cell_os_close(cell_os_file __this) {
    if(__this == CELL_NULL)
        return __this_error;

    int res;

    if((res = os_linux_sys_close(__this->fd)) < 0) {
        return cell_os_error[os_linux_sys_errno];
    }

    __this->fd = -1;

    return CELL_NULL;
}
