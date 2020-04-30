/* 
 * Manual memory management library for cell language
 * Copyright (c) 2018 Armands Arseniuss Skolmeisters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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

#ifndef __CELL__MEM_STRING_H__
#    define __CELL__MEM_STRING_H__

#    include <cell/string.h>
#    include <cell/slice.h>
#    include <cell/error.h>

cell_error cell_string_copy(cell_string * str, const cell_slice_type * slice, cell_size sz);
cell_error cell_string_copy_s(cell_string * s1, const cell_string * s2);

#endif /* !__CELL__MEM_STRING_H__ */
