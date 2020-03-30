/* 
 * I/O library for cell language
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
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

#ifndef __CELL__STD_IO_H__
#    define __CELL__STD_IO_H__

#    include <cell/error.h>


#define cell_io_printf(fmt, ...) \
    _Generic((fmt), \
        const char*: cell_io_printf_p, \
        char*: cell_io_printf_p, \
        cell_string: cell_io_printf_s \
    )(fmt, ##__VA_ARGS__)

// func printf(fmt string, ...) error
cell_error cell_io_printf_s(cell_string fmt, ...);

cell_error cell_io_printf_p(const char* fmt, ...);

#endif /* __CELL__STD_IO_H__ */
