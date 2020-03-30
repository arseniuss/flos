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

#include <cell/assert.h>
#include <cell/io.h>
#include <cell/fmt.h>
#include <cell/os/file.h>

cell_error cell_io_printf_s(cell_string fmt, ...) {
    cell_va_list v;
    cell_array_make(a, 4096, cell_byte);
    cell_error err;
    
    cell_va_start(v, fmt);
    
    cell_array_sliceof(a, 0, 0, s);
    
    if((err = cell_fmt_format_list((cell_slice_type *)&s, fmt, v)) != CELL_NULL) return err;
    
    if((err = cell_os_write_a(stdout, (cell_slice_type *)&s)) != CELL_NULL) return err;
    
    return CELL_NULL;
}

cell_error cell_io_printf_p(const char* fmt, ...) {
    cell_va_list v;
    cell_array_make(a, 4096, cell_byte);
    cell_error err;
    
    cell_va_start(v, fmt);
    
    cell_array_sliceof(a, 0, 0, s);
    
    if((err = cell_fmt_format_list((cell_slice_type *)&s, cell_string_c(fmt), v)) != CELL_NULL) return err;
    
    if((err = cell_os_write_a(stdout, (cell_slice_type *)&s)) != CELL_NULL) return err;
    
    return CELL_NULL;
}
