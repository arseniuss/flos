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
