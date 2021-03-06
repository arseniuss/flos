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

#ifndef __CELL__LANG_TARGET_H__
#    define __CELL__LANG_TARGET_H__

#    include <cell/string.h>

struct cell_lang_target_s;

typedef struct cell_lang_target_s *cell_lang_target;

cell_error cell_lang_target_file(cell_string str, cell_lang_target * trg);

cell_error cell_lang_target_name(const cell_lang_target trg, cell_string * name);

cell_error cell_lang_target_write(cell_lang_target trg, const cell_string str);

#endif /* !__CELL__LANG_TARGET_H__ */
