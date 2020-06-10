/**
 *  Cell language token library
 *  Copyright (C) 2019  Armands Arseniuss Skolmeisters
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

#ifndef __CELL__TOKEN_INTERNAL_H__
#    define __CELL__TOKEN_INTERNAL_H__

#    include <cell/lang/source.h>
#    include <cell/os/file.h>

struct __source_file_s {
    cell_os_file file;
    cell_string name;
};

struct __source_str_s {
    cell_string str;
    cell_byte *ptr;
};

cell_error __source_file_read(const cell_lang_source src, cell_char * _ch, cell_slice_type * buf,
                              cell_lang_position * pos);

cell_error __source_str_read(const cell_lang_source src, cell_char * ch, cell_slice_type * buf,
                             cell_lang_position * pos);

#endif /* !__CELL__TOKEN_INTERNAL_H__ */
