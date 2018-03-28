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

#include <os/linux/defs.h>

#if __ARCH__ != amd64
#error Wrong __ARCH__ value!
#endif

#ifdef NAMESPACE
#undef NAMESPACE
#endif
#define NAMESPACE os_linux
#include <cell/namespace.h>

uintptr_t afunc(_syscall)(uintptr_t a, uintptr_t b, uintptr_t c, uintptr_t d, uintptr_t e, uintptr_t f, uintptr_t num)
{
    uintptr_t ret = (uintptr_t)-1;
    
    __asm__ __volatile__
    (
            "movq %2, %%rdi;"
            "movq %3, %%rsi;"
            "movq %4, %%rdx;"
            "movq %5, %%r10;"
            "movq %6, %%r8;"
            "movq %7, %%r9;"
            "movq %1, %%rax;"
            "syscall;"
            : "=a"(ret) // output
            : "a"(num), "D"(a), "S"(b), "d"(c), "r"(d), "r"(e), "r"(f) // input
            : "rcx", "r11" // clobers
    );
    
    return (uintptr_t)ret;
} 
