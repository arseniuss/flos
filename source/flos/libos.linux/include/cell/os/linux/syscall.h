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

#ifndef __CELL__OS_LINUX_SYSCALL_H__
#    define __CELL__OS_LINUX_SYSCALL_H__

#    define SYSCALL_NAME(name)                                          os_linux_sys_##name

#    define SYSCALL_PROC1(name, t0, r0)                                 void os_linux_sys_##name(t0 r0)
#    define SYSCALL_FUNC1(name, rettype, t0, r0)                        rettype os_linux_sys_##name(t0 r0)
#    define SYSCALL_FUNC3(name, rettype, t0, r0,t1,  r1, t2, r2)        rettype os_linux_sys_##name(t0 r0, t1 r1, t2 r2)

#    define SYSCALL_PROC1_CALL(name, r0)                                os_linux_sys##name((r0))

#endif /* __CELL__OS_LINUX_SYSCALL_H__ */
