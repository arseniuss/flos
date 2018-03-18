#pragma once

#include <os/linux/defs.h>

#if __ARCH__ == amd64
#include "amd64/syscall.h"
#else
#error __ARCH__ is not defined!
#endif

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

#define SYSCALL_PROC1(name, t0, r0) \
    void linux_##name(t0 r0) \
    {\
        check(syscall(SYSCALL_##name, (long)r0, 0, 0, 0, 0, 0)); \
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

    