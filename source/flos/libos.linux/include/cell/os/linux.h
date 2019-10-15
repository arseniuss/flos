/**
 *  Linux layer library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
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

#ifndef __CELL__OS_LINUX_H__
#    define __CELL__OS_LINUX_H__

#    include <cell/os/linux/defs.h>
#    include <cell/os/linux/syscall.h>

extern cell_uintptr os_linux_sys_errno;

SYSCALL_PROC1(exit, cell_uint32, error_code);

SYSCALL_FUNC1(fork, linux_pid_t, struct linux_pt_regs *, regs);

SYSCALL_FUNC3(read, cell_ssize, int, fd, void *, buf, cell_size, count);

SYSCALL_FUNC3(write, cell_ssize, int, fd, const void *, buf, cell_size, count);

SYSCALL_FUNC3(open, int, const char *, pathname, int, flags, int, mode);

SYSCALL_FUNC1(close, long, unsigned int, fd);

SYSCALL_FUNC1(brk, int, void *, ptr);

#endif /* __CELL__OS_LINUX_H__ */
