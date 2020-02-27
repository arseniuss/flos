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

#include <cell/mem.h>
#include <cell/lang/scanner.h>
#include <cell/utf8.h>

#include "internal.h"

#define BOM             0xFEFF

cell_error cell_lang_scanner_new(cell_lang_scanner * scn, cell_lang_source src) {
    cell_error err;
    cell_lang_scanner s;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_scanner_s), (void **)&s)) != CELL_NULL) {
        return err;
    }

    s->src = src;

    *scn = s;

    return CELL_NULL;
}
