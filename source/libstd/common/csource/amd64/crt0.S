.section .text
.global _start
.extern main
.extern _init
_start:
    # Set up end of the stack frame linked list.
    movq $0, %rbp
    pushq %rbp # rip=0
    pushq %rbp # rbp=0
    movq %rsp, %rbp

    // TODO: push main params

    // TODO: init stuff

    call _init

    // TODO: restore main params

    call main

    # Terminate the process with the exit code.
    movl %eax, %edi
    call os_exit
_1:
    jmp _1
.size _start, . - _start

    