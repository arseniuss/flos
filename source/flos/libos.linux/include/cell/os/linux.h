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

#ifndef __CELL__OS_LINUX_H__
#    define __CELL__OS_LINUX_H__

#    include <cell/os/linux/defs.h>
#    include <cell/os/linux/syscall.h>

extern cell_uintptr os_linux_sys_errno;

#    ifdef SYSCALL_DEF
#        undef SYSCALL_DEF
#    endif
       /*
        * SYSCALL_DEF 
        */

#    define SYSCALL_DEF(no, name, param_count, ret_type, ...) \
        SYSCALL_DEF##param_count(no, name, ret_type, ##__VA_ARGS__)

#    ifdef SYSCALL_DEF1
#        undef SYSCALL_DEF1
#    endif

#    define SYSCALL_DEF1(no, name, rettype, t0, r0) \
    rettype os_linux_sys_##name(t0 r0);

#    ifdef SYSCALL_DEF2
#        undef SYSCALL_DEF2
#    endif

#    define SYSCALL_DEF2(no, name, rettype, t0, r0, t1, r1) \
    rettype os_linux_sys_##name(t0 r0, t1 r1);

#    ifdef SYSCALL_DEF3
#        undef SYSCALL_DEF3
#    endif

#    define SYSCALL_DEF3(no, name, rettype, t0, r0, t1, r1, t2, r2) \
    rettype os_linux_sys_##name(t0 r0, t1 r1, t2 r2);

#    ifdef SYSCALL_DEF6
#        undef SYSCALL_DEF6
#    endif

#    define SYSCALL_DEF6(no, name, rettype, t0, r0, t1, r1, t2, r2, t3, r3, t4, r4, t5, r5) \
    rettype os_linux_sys_##name(t0 r0, t1 r1, t2 r2, t3 r3, t4 r4, t5 r5);


#    include <cell/os/linux/amd64/syscalls.inc.h>

#    undef SYSCALL_DEF
#    undef SYSCALL_DEF1
#    undef SYSCALL_DEF2
#    undef SYSCALL_DEF3
#    undef SYSCALL_DEF6

#endif /* __CELL__OS_LINUX_H__ */
