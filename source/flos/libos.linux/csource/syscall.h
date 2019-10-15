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

#pragma once

#define SYSCALL_read        0
#define SYSCALL_write       1
#define SYSCALL_open        2
#define SYSCALL_close       3
#define SYSCALL_stat        4
#define SYSCALL_fstat       5
#define SYSCALL_lstat       6
#define SYSCALL_poll        7

#define SYSCALL_brk         12

#define SYSCALL_fork        57

#define SYSCALL_exit        60
