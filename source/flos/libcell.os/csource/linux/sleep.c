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

#include <cell/os/time.h>
#include <cell/os/linux.h>
#include <cell/os/error.h>

#define MAX_NSECS   1000000000

cell_error cell_os_sleep(cell_uint64 milisecs) {
    struct linux_timespec req;
    struct linux_timespec rem;

    milisecs *= 1000000;

    req.tv_sec = milisecs / MAX_NSECS;
    req.tv_nsec = milisecs % MAX_NSECS;

    if(os_linux_sys_nanosleep(&req, &rem) != 0) {
        return cell_os_error[os_linux_sys_errno];
    }

    return CELL_NULL;
}
