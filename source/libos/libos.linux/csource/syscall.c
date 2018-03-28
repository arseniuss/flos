/* 
 * This file is part of the libos distribution for cell standard library
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <os/linux/defs.h>
#include <os/linux/syscall.h>

#include "internal.h"

static long errno = 0;

long* __errno_location()
{
    return &errno;
}

SYSCALL_PROC1(exit, int, error_code);
        
SYSCALL_FUNC1(fork, pid_t, struct pt_regs*, regs);

SYSCALL_FUNC3(read, ssize_t, int, fd, void*, buf, size_t, count)
        
SYSCALL_FUNC3(write, ssize_t, int, fd, const void*, buf, size_t, count)
        
SYSCALL_FUNC3(open, int, const char*, pathname, int, flags, int, mode)

