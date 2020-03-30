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

#ifndef __CELL_LINUX__DEFS_H__
#    define __CELL_LINUX__DEFS_H__

#    include <cell/builtin.h>

//TODO: POSIX, UNIX
#    define CELL_LINUX_O_RDONLY     00000000
#    define CELL_LINUX_O_WRONLY     00000001
#    define CELL_LINUX_O_RDWR		00000002
#    define CELL_LINUX_O_CREAT		00000100


#    define CELL_LINUX_S_IRWXU 00700
#    define CELL_LINUX_S_IRUSR 00400
#    define CELL_LINUX_S_IWUSR 00200
#    define CELL_LINUX_S_IXUSR 00100

#    define CELL_LINUX_S_IRWXG 00070
#    define CELL_LINUX_S_IRGRP 00040
#    define CELL_LINUX_S_IWGRP 00020
#    define CELL_LINUX_S_IXGRP 00010

#    define CELL_LINUX_S_IRWXO 00007
#    define CELL_LINUX_S_IROTH 00004
#    define CELL_LINUX_S_IWOTH 00002
#    define CELL_LINUX_S_IXOTH 00001

typedef int cell_linux_pid_t;
typedef int cell_linux_off_t;   // TODO
typedef long int cell_linux_time_t;

struct cell_linux_pt_regs {
    long reg[8];
};

struct cell_linux_stat;         // TODO

struct cell_linux_timespec {
    cell_linux_time_t tv_sec;
    long tv_nsec;
};

#endif /* !__CELL_LINUX__DEFS_H__ */
