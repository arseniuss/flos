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