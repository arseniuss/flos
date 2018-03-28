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
#pragma once

#include <os/linux/defs.h>
#include <os/linux/syscall.h>

#define syscall(...)    CONCAT(__ARCH__, __syscall)(__VA_ARGS__)

long syscall(long num, long a, long b, long c, long d, long e, long f);

long* __errno_location();

static long check(long ret)
{
    if(ret >= (unsigned long)-4095) {
        long err = ret;
        *(__errno_location()) = (-err);
        ret = (unsigned long)-1;
    }
    
    return (long)ret;
}

#ifdef SYSCALL_PROC1
#undef SYSCALL_PROC1
#endif

#define SYSCALL_PROC1(name, t0, r0)     \
    void linux_##name(t0 r0) \
    {\
        check(syscall(CONCAT(SYSCALL_, name), (long)r0, 0, 0, 0, 0, 0)); \
    }

#ifdef SYSCALL_FUNC1
#undef SYSCALL_FUNC1
#endif

#define SYSCALL_FUNC1(name, rettype, t0, r0) \
    rettype linux_##name(t0 r0) \
    {\
        return check(syscall(SYSCALL_##name, (long)r0, 0, 0, 0, 0, 0)); \
    }

#ifdef SYSCALL_FUNC3
#undef SYSCALL_FUNC3
#endif

#define SYSCALL_FUNC3(name, rettype, t0, r0,t1,  r1, t2, r2) \
    rettype linux_##name(t0 r0, t1 r1, t2 r2) \
    {\
        return check(syscall(SYSCALL_##name, (long)r0, (long)r1, (long)r2, 0, 0, 0)); \
    }

    