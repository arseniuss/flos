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
#include <cell/std/fmt.h>

cell_error *io_printf(cell_string fmt, ...) {
    cell_va_list v;
    cell_array_make(a, 0, 4096);
    cell_error *err;
    
    cell_va_start(v, fmt);
    
    if((err = fmt_format_list(&a, fmt, v)) != CELL_NULL) return err;
    
    if((err = os_write(1, a.buffer, a.len, CELL_NULL)) != CELL_NULL) return err;
    
    return CELL_NULL;
}
