/**
 *  Linux layer library
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

#include <cell/linux.h>
#include <cell/linux/defs.h>

#include "internal.h"

cell_uintptr cell_linux_sys_errno = 0;

cell_uintptr *cell_linux_errno_location() {
    return &cell_linux_sys_errno;
}

#ifdef SYSCALL_DEF
#    undef SYSCALL_DEF
#endif /* SYSCALL_DEF */

#define SYSCALL_DEF(no, name, param_count, ret_type, ...) \
        SYSCALL_DEF##param_count(no, name, ret_type, ##__VA_ARGS__)

#ifdef SYSCALL_DEF1
#    undef SYSCALL_DEF1
#endif

#define SYSCALL_DEF1(no, name, rettype, t0, r0) \
    rettype cell_linux_sys_##name(t0 r0) \
    {\
        cell_uintptr ret = cell_linux_syscall(no, (cell_uintptr)r0, 0, 0, 0, 0, 0);\
        \
        ret = cell_linux_check_syscall(ret);\
        \
        return ret; \
    }

#ifdef SYSCALL_DEF2
#    undef SYSCALL_DEF2
#endif

#define SYSCALL_DEF2(no, name, rettype, t0, r0, t1, r1) \
    rettype cell_linux_sys_##name(t0 r0, t1 r1) \
    {\
        cell_uintptr ret = cell_linux_syscall(no, (cell_uintptr)r0, (cell_uintptr)r1, 0, 0, 0, 0);\
        \
        ret = cell_linux_check_syscall(ret); \
        \
        return ret;\
    }

#ifdef SYSCALL_DEF3
#    undef SYSCALL_DEF3
#endif

#define SYSCALL_DEF3(no, name, rettype, t0, r0, t1, r1, t2, r2) \
    rettype cell_linux_sys_##name(t0 r0, t1 r1, t2 r2) \
    {\
        cell_uintptr ret = cell_linux_syscall(no, (cell_uintptr)r0, (cell_uintptr)r1, (cell_uintptr)r2, 0, \
            0, 0);\
        \
        ret = cell_linux_check_syscall(ret); \
        \
        return ret;\
    }

#ifdef SYSCALL_DEF6
#    undef SYSCALL_DEF6
#endif

#define SYSCALL_DEF6(no, name, rettype, t0, r0, t1, r1, t2, r2, t3, r3, t4, r4, t5, r5) \
    rettype cell_linux_sys_##name(t0 r0, t1 r1, t2 r2, t3 r3, t4 r4, t5 r5) \
    {\
        cell_uintptr ret = cell_linux_syscall(no, (cell_uintptr)r0, (cell_uintptr)r1, (cell_uintptr)r2, \
            (cell_uintptr)r3, (cell_uintptr)r4, (cell_uintptr)r5);\
        \
        ret = cell_linux_check_syscall(ret); \
        \
        return ret;\
    }


#include <cell/linux/syscalls.inc.h>

#undef SYSCALL_DEF
