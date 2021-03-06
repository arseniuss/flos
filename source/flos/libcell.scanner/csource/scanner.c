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

    if((err = cell_mem_alloc(256, (void **)&s->buf.buf)) != CELL_NULL) {
        cell_mem_free(s);
        return err;
    }

    s->buf.len = 0;
    s->buf.cap = 256;

    s->src = src;
    cell_lang_position_init(&s->pos);
    cell_lang_position_init(&s->last_pos);

    *scn = s;

    return CELL_NULL;
}

cell_error cell_lang_scanner_err(cell_lang_scanner scn) {
    return scn->err;
}

cell_lang_source cell_lang_scanner_source(cell_lang_scanner scn) {
    return scn->src;
}
