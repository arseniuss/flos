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
#include <cell/os/linux.h>
#include <cell/os/mem.h>

cell_error cell_os_sbrk(cell_uint32 inc, void **ptr) {
    cell_uint64 res;
    static cell_uintptr last_position = CELL_NULL;

    if(last_position == CELL_NULL) {
        if(((cell_int64) (res = os_linux_sys_brk(last_position))) - last_position < 0) {
            return cell_os_error[os_linux_sys_errno];
        }
        last_position = res;
    }

    cell_uintptr new_addr = last_position + inc;

    if(((cell_int64) (res = os_linux_sys_brk(new_addr))) - last_position < 0) {
        return cell_os_error[os_linux_sys_errno];
    }

    if(ptr)
        *ptr = (void *)last_position;

    last_position = new_addr;

    return CELL_NULL;
}
