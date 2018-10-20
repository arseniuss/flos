/* 
 * Standard Linux layer for cell language
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
#include <cell/os/linux.h>

#include "internal.h"
#include "syscall.h"

static uintptr_t errno = 0;

uintptr_t *os_linux_errno_location() {
    return &errno;
}



SYSCALL_FUNC1(fork, linux_pid_t, struct linux_pt_regs *, regs);

SYSCALL_FUNC3(read, ssize_t, int, fd, void *, buf, size_t, count)
SYSCALL_FUNC3(write, ssize_t, int, fd, const void *, buf, size_t, count)
SYSCALL_FUNC3(open, int, const char *, pathname, int, flags, int, mode)
SYSCALL_PROC1(exit, uint32_t, error_code)
