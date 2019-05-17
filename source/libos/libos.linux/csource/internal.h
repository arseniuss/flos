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
#pragma once

#include <cell/os/linux/defs.h>
#include <cell/os/linux/syscall.h>

cell_uintptr os_linux_syscall(cell_uintptr num, cell_uintptr a, cell_uintptr b,
                              cell_uintptr c, cell_uintptr d, cell_uintptr e);

cell_uintptr *os_linux_errno_location();

static inline cell_uintptr os_linux_check_syscall(cell_uintptr ret) {
    if(ret >= (cell_uintptr) - 4095) {
        cell_uintptr err = ret;
        *(os_linux_errno_location()) = (-err);
        ret = (cell_uintptr) - 1;
    }

    return (cell_uintptr) ret;
}



#ifdef SYSCALL_PROC1
#    undef SYSCALL_PROC1
#endif

#define SYSCALL_PROC1(name, t0, r0)     \
    void os_linux_sys_##name(t0 r0) \
    {\
        cell_uintptr ret = os_linux_syscall(SYSCALL_##name, (cell_uintptr)r0, 0, 0, 0, 0); \
        \
        os_linux_check_syscall(ret); \
    }

#ifdef SYSCALL_FUNC1
#    undef SYSCALL_FUNC1
#endif

#define SYSCALL_FUNC1(name, rettype, t0, r0) \
    rettype os_linux_sys_##name(t0 r0) \
    {\
        cell_uintptr ret = os_linux_syscall(SYSCALL_##name, (cell_uintptr)r0, 0, 0, 0, 0);\
        \
        ret = os_linux_check_syscall(ret);\
        \
        return ret; \
    }

#ifdef SYSCALL_FUNC3
#    undef SYSCALL_FUNC3
#endif

#define SYSCALL_FUNC3(name, rettype, t0, r0,t1,  r1, t2, r2) \
    rettype os_linux_sys_##name(t0 r0, t1 r1, t2 r2) \
    {\
        cell_uintptr ret = os_linux_syscall(SYSCALL_##name, (cell_uintptr)r0, (cell_uintptr)r1, (cell_uintptr)r2, 0, 0);\
        \
        ret = os_linux_check_syscall(ret); \
        \
        return ret;\
    }
