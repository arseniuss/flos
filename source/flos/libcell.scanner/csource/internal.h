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

#ifndef __CELL__SCANNER_INTERNAL_H__
#    define __CELL__SCANNER_INTERNAL_H__

#    include <cell/lang/source.h>

struct cell_lang_scanner_s {
    cell_lang_source src;

    void (*err_handler) (const cell_byte * msg);

    char ch;
    /** Byte offset in file */
    int offset;

    /** Character offset in file */
    int choffset;

    int err_count;
};

#endif /* __CELL__SCANNER_INTERNAL_H__ */
