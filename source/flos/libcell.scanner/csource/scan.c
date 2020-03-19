/**
 *  Cell language scanner library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
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

#include <cell/array.h>
#include <cell/assert.h>
#include <cell/lang/scanner.h>
#include <cell/ascii.h>
#include <cell/mem.h>

#include "internal.h"

// func (scn scanner) scan() (token, position, string)

cell_lang_token cell_lang_scanner_scan(cell_lang_scanner scn, cell_lang_position * pos, cell_string * str) {
    cell_error err;

    if(pos)
        pos->line = 0, pos->offset = 0;

    cell_array_make(tmp, 0, 256);

    if((err = scn->src->read(scn->src, &tmp)) != CELL_NULL)
        return CELL_LANG_TINVALID;

    if(tmp.len > 0 &&  cell_ascii_isalpha(tmp.buffer[0])) {
        while(cell_ascii_isalnum(tmp.buffer[tmp.len - 1])) {
            if((err = scn->src->read(scn->src, &tmp)) != CELL_NULL)
                return CELL_LANG_TINVALID;
        }

        void *str;

        cell_mem_alloc(tmp.len, &str);

        return CELL_LANG_TIDENT;
    }

    return CELL_LANG_TEOF;
}
