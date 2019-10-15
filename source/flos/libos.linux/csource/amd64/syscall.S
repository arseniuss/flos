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
/**
 * On amd64/x86_64 syscall number is passed in rax register
 * Parameters are passed in: rdi, rsi, rdx, r10, r8, r9
 *
 * This is a bit different from SysV calling convention, where parameters are 
 * passed: rdi, rsi, rdx, rcx, r8, r9
 *
 */
// module os.linux
// func syscall(num, a, b, c, d, e uint64) uint64
    .globl os_linux_syscall
os_linux_syscall:
movq % rdi, %rax                       // #1 (rdi) -> rax
    movq % rsi, %rdi                   // #2 (rsi) -> #1 (rdi)
    movq % rdx, %rsi                   // #3 (rdx) -> #2 (rsi)
    movq % rcx, %rdx                   // #4 (rcx) -> #3 (rdx)
    movq % r8, %r10                    // #5 (r8)  -> #4 (r10)
    movq % r9, %r8                     // #6 (r9)  -> #5 (r8)
    syscall
    // syscall return value is passed in rax so everything is ok
    ret
