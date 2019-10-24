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

#include <cell/os.h>
#include <cell/os/linux.h>

cell_error *os_close(fd_t fd) {
    long res = os_linux_sys_close(fd);

    if(res != 0) {
        return os_error[-os_linux_sys_errno];
    }

    return CELL_NULL;
}

cell_error *os_open(fd_t * fd, const cell_string file, cell_byte omode) {
    int flags = 0, mode = 0;

    flags |= omode & 0x3;              // read, write same as POSIX

    fd_t res = os_linux_sys_open((const char *)file.buffer, flags, mode);

    if(res < 0) {
        return os_error[-os_linux_sys_errno];
    }

    *fd = res;

    return CELL_NULL;
}

void os_exit(const cell_string msg) {
    os_linux_sys_write(1, msg.buffer, msg.len);

    os_linux_sys_exit(msg.len == 0 ? 0 : 1);
}

cell_error *os_write(fd_t fd, const void *buf, cell_size bytes,
                     cell_ssize * written) {
    cell_ssize res = os_linux_sys_write(fd, buf, bytes);

    if(res < 0) {
        return os_error[-os_linux_sys_errno];
    }

    if(written)
        *written = res;

    return CELL_NULL;
}

cell_error *os_sbrk(cell_uint32 inc, void **ptr) {
    cell_uint64 res;
    static cell_uintptr last_position = CELL_NULL;

    if(last_position == CELL_NULL) {
        if(((cell_int64) (res = os_linux_sys_brk(last_position))) -
           last_position < 0) {
            return os_error[-os_linux_sys_errno];
        }
        last_position = res;
    }

    cell_uintptr new_addr = last_position + inc;

    if(((cell_int64) (res = os_linux_sys_brk(new_addr))) - last_position < 0) {
        return os_error[-os_linux_sys_errno];
    }

    if(ptr)
        *ptr = (void *)last_position;

    last_position = new_addr;

    return CELL_NULL;
}
