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
#    include <cell/os.h>

// type file struct {
// 
// }

typedef struct {
    fd_t fd;
} file;

//
// var f file("file.f", READ)
//
// func init(filename string, mode int) (file, error)

struct file_init_res {
    file f;
    cell_error *err;
} file_init(cell_string filename, int mode);

// func open() (file, error)

#    define file_write(f, data)     _Generic((data), \
                                    int: file_write_i, \
                                    default: file_write \
                                    )(f, data)

// func (f* file) write(data [?]byte, len int) 


// func (f *file) read(data [?]byte, len int) error
cell_error file_read(file * f, const cell_byte data[], cell_size len);

// func (f *file) close() error
cell_error *file_close(file * f);

#endif /* __CELL__STD_IO_H__ */
