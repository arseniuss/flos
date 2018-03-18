#pragma once

#define SYSCALL_exit    0x1
#define SYSCALL_fork    0x2
#define SYSCALL_read    0x3
#define SYSCALL_write   0x4
#define SYSCALL_open    0x5
#define SYSCALL_close   0x6
// TODO: finish


#define SYSCALL_PROC1(name, t0, r0)                                 void linux_##name(t0 r0)
#define SYSCALL_FUNC1(name, rettype, t0, r0)                        rettype linux_##name(t0 r0)
#define SYSCALL_FUNC3(name, rettype, t0, r0,t1,  r1, t2, r2)        rettype linux_##name(t0 r0, t1 r1, t2 r2)