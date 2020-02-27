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

#ifndef __CELL__OS_LINUX_DEFS_H__
#    define __CELL__OS_LINUX_DEFS_H__

#    include <cell/builtin.h>

#    define O_RDONLY	00000000
#    define O_WRONLY	00000001
#    define O_RDWR		00000002
#    define O_CREAT		00000100


#    define S_IRWXU 00700
#    define S_IRUSR 00400
#    define S_IWUSR 00200
#    define S_IXUSR 00100

#    define S_IRWXG 00070
#    define S_IRGRP 00040
#    define S_IWGRP 00020
#    define S_IXGRP 00010

#    define S_IRWXO 00007
#    define S_IROTH 00004
#    define S_IWOTH 00002
#    define S_IXOTH 00001

typedef int linux_pid_t;
typedef int off_t;              // TODO
typedef long int time_t;

struct linux_pt_regs {
    long reg[8];
};

struct linux_stat;              // TODO

struct linux_timespec {
    time_t tv_sec;
    long tv_nsec;
};

#endif /* __CELL__OS_LINUX_DEFS_H__ */
