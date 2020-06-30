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
#include <cell/linux.h>
#include <cell/mem.h>
#include <cell/os/error.h>
#include <cell/os/file.h>

#include "internal.h"

cell_error cell_os_create(cell_string name, cell_os_file * ret1) {
    if(ret1 == CELL_NULL)
        return __ret1_error;

    int res;

    if((res = cell_linux_sys_open(name.buffer, CELL_LINUX_O_CREAT | CELL_LINUX_O_RDWR, 0666)) < 0) {
        return cell_os_error[cell_linux_sys_errno];
    }
    
    cell_error err;
    if((err = cell_mem_alloc(sizeof(struct os_file_s), (void **)ret1)) != CELL_NULL) {
        return err;
    }

    (*ret1)->fd = res;

    return CELL_NULL;
}
