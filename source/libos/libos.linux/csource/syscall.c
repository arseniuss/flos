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

