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

#include <cell/std/io.h>
#include <cell/os.h>
#include <cell/builtin.h>
#include <cell/error.h>
#include <cell/assert.h>

struct file_init_res file_init(cell_string filename, int mode) {
    fd_t fd;
    struct file_init_res res;

    cell_error *err = os_open(&fd, filename, mode);
    if(err)
        return (res.err = err, res);

    res.f.fd = fd;

    return res;
}

cell_error *file_close(file * f) {
    cell_error *err;

    cell_assert(f);

    if((err = os_close(f->fd)) == CELL_NULL) {
        f->fd = -1;
    }

    return err;
}
