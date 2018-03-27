long amd64__syscall(long num, long a, long b, long c, long d, long e, long f)
{
    long ret;
    
    register long callreg __asm__("eax") = (long)num;
    register long arg0 __asm__("rdi") = (long)a;
    register long arg1 __asm__("rsi") = (long)b;
    register long arg2 __asm__("rdx") = (long)c;
    register long arg3 __asm__("r10") = (long)d;
    register long arg4 __asm__("r8") = (long)e;
    register long arg5 __asm__("r9") = (long)f;
    
    __asm__ __volatile__(
            "syscall"
            : "=a"(ret)
    );
    
    return (long)ret;
} 
