/* 
 * Standard formatting for cell language
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
#ifndef __CELL__STD_FMT_H__
#    define __CELL__STD_FMT_H__

#    include <cell/args.h>
#    include <cell/string.h>
#    include <cell/type.h>
#    include <cell/error.h>
#    include <cell/array.h>

const cell_uint32 fmt_width;
const cell_uint32 fmt_left;
const cell_uint32 fmt_show_sign;
const cell_uint32 fmt_blank;
const cell_uint32 fmt_alter;
const cell_uint32 fmt_zeros;
const cell_uint32 fmt_signed;
const cell_uint32 fmt_w16;
const cell_uint32 fmt_w32;
const cell_uint32 fmt_w64;

typedef struct {
    cell_byte *begin;

    cell_char ch;

    cell_int16 width;
    cell_uint16 precision;
    cell_uint32 flags;
} fmt_format_args;

cell_error *fmt_format(cell_array * buffer, cell_string format, ...);
cell_error *fmt_format_list(cell_array * buffer, cell_string format, cell_va_list list);

#endif /* __CELL__STD_FMT_H__ */
