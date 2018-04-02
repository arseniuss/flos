# amd64 calling convention

This file describes _amd64_ architecture's calling convention.


| Platform | Return value | Parameter registers | Additional parameters | Stack alignment | Scratch registers | Preserved registers | Call list |
| ------------- | ------------------- | ----------------------------- | ---------------------------------- | ------------------------ | ------------------------ | ----------------------------- | ---------- |
|  System V x86_64 <sup>1</sup> | rax, rdx | rdi, rsi, rdx, rcx, r8, r9 | stack (right to left) | 16 byte at call <sup>2</sup> | rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11 | rbx, rsp, rbp, r12, r13, r14, r15  | rbp  |

<sup>1</sup> There is 128 byte area below stack called 'red zone', which can be used by leaf function without incresing rsp register.

<sup>2</sup> The called function is allowed to modify the arguments on the stack and the caller must not assume the stack parameters are preserved. The caller should clean up the stack.

Thanks to osdev.org community wiki ^[1](https://wiki.osdev.org/Calling_Conventions).