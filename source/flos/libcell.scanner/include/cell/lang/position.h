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

#ifndef __CELL__LANG_POSITION_H__
#    define __CELL__LANG_POSITION_H__

#    include <cell/string.h>

struct cell_lang_position_s {
    int line;
    int offset;
};

typedef struct cell_lang_position_s cell_lang_position;

static inline void cell_lang_position_init(cell_lang_position * pos) {
    pos->line = -1;
    pos->offset = -1;
}

// func (p *pos) string() string
cell_string cell_lang_pos_string(cell_lang_position *);

#endif /* __CELL__LANG_POSITION_H__ */
