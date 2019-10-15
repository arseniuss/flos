/**
 *  Linux layer library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
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

#define __ASSEMBLY__

.section .text
.globl _start 
.extern os_linux_syscall
.extern main
_start:
    xor %ebp, %ebp 

    mov (%rsp), %edi 
    lea 8(%rsp), %rsi
    lea 16(%rsp,%rdi,8), %rdx
       
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx

    call _init

    popq %rcx
    popq %rsi
    popq %rdx
    popq %rcx

    xor %rax, %rax

    call main

    pushq %rax

    call _fini

    popq %rax
    
    movq %rax, %rdi
    call os_linux_sys_exit
    ret

