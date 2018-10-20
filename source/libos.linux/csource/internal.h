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

uintptr_t os_linux_syscall(uintptr_t num, uintptr_t a, uintptr_t b, uintptr_t c,
                           uintptr_t d, uintptr_t e);

uintptr_t *os_linux_errno_location();

static inline uintptr_t os_linux_check_syscall(uintptr_t ret) {
    if(ret >= (uintptr_t) - 4095) {
        uintptr_t err = ret;
        *(os_linux_errno_location()) = (-err);
        ret = (uintptr_t) - 1;
    }

    return (uintptr_t) ret;
}



#ifdef SYSCALL_PROC1
#    undef SYSCALL_PROC1
#endif

#define SYSCALL_PROC1(name, t0, r0)     \
    void os_linux_sys_##name(t0 r0) \
    {\
        uintptr_t ret = os_linux_syscall(SYSCALL_##name, (uintptr_t)r0, 0, 0, 0, 0); \
        \
        os_linux_check_syscall(ret); \
    }

#ifdef SYSCALL_FUNC1
#    undef SYSCALL_FUNC1
#endif

#define SYSCALL_FUNC1(name, rettype, t0, r0) \
    rettype os_linux_sys_##name(t0 r0) \
    {\
        uintptr_t ret = os_linux_syscall(SYSCALL_##name, (uintptr_t)r0, 0, 0, 0, 0);\
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
        uintptr_t ret = os_linux_syscall(SYSCALL_##name, (uintptr_t)r0, (uintptr_t)r1, (uintptr_t)r2, 0, 0);\
        \
        ret = os_linux_check_syscall(ret); \
        \
        return ret;\
    }
