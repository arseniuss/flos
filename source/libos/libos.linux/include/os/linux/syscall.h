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

#include <cell/defs.h>

#ifdef NAMESPACE
#undef NAMESPACE
#endif
#define NAMESPACE os_linux

#include <cell/namespace.h>

#define SYSCALL_PROC1(name, t0, r0)                                 void func(sys_##name)(t0 r0)
#define SYSCALL_FUNC1(name, rettype, t0, r0)                        rettype func(sys_##name)(t0 r0)
#define SYSCALL_FUNC3(name, rettype, t0, r0,t1,  r1, t2, r2)        rettype func(sys_##name)(t0 r0, t1 r1, t2 r2)