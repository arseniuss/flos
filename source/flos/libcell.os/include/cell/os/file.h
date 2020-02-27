/**
 *  OS layer library
 *  Copyright (C) 2019 Armands Arseniuss Skolmeisters
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

#ifndef __CELL__OS_FILE_H__
#    define __CELL__OS_FILE_H__

#    include <cell/array.h>
#    include <cell/builtin.h>
#    include <cell/error.h>
#    include <cell/string.h>

// cell: type file
typedef struct os_file_s *cell_os_file;

extern cell_os_file stdin;
extern cell_os_file stdout;
extern cell_os_file stderr;

/**
 * 
 */
// cell: func chdir(dir string) error
cell_error cell_os_chdir(cell_string dir);

/**
 * Creates new file. If file already exists, it is truncated; otherwise it is created with 0666 permissions. On success
 * file is opened for reading and writing.
 */
// cell: func create(name string) (file, error)
cell_error cell_os_create(cell_string name, cell_os_file * out1);

/**
 * 
 */
// cell: func open(name string) (file, error)
cell_error cell_os_open(cell_string name, cell_os_file * out1);

/**
 * 
 */
// cell: func (f file) close() error
cell_error cell_os_close(cell_os_file __this);

/**
 * 
 */
// cell: func (f file) write(a array) error
cell_error cell_os_write_a(cell_os_file __this, cell_array arg1);

cell_error cell_os_write_s(cell_os_file __this, cell_string arg1);


#    define cell_os_write(o, arg)        \
                _Generic((arg), \
                    cell_array: cell_os_write_a, \
                    cell_string: cell_os_write_s \
                )(o, arg)

/**
 * 
 */
// cell: func (f file) read() ([], error)
cell_error cell_os_read(cell_os_file __this, cell_array * ret1);

#endif /* !__CELL__OS_FILE_H__ */
