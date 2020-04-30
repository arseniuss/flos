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


#ifndef __CELL__LANG_SOURCE_H__
#    define __CELL__LANG_SOURCE_H__

#    include <cell/builtin.h>
#    include <cell/string.h>
#    include <cell/error.h>
#    include <cell/slice.h>

typedef struct cell_lang_source_s *cell_lang_source;

struct cell_lang_source_s {
    // func (src source) read() (int16, error)
    cell_error(*read) (const cell_lang_source src, cell_char * ch, cell_slice_type * buf);

    void *data;
};

typedef struct cell_lang_source_s *cell_lang_source;

// func (src *source) new(filepath string) error

// func new(filepath string) (error, source)
cell_error cell_lang_source_new(cell_string filepath, cell_lang_source * src);

// func string(str string) (error, source)
cell_error cell_lang_source_string(cell_string str, cell_lang_source * src);

#endif /* __CELL__LANG_SOURCE_H__ */
