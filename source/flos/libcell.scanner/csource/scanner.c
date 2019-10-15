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

#include <cell/std/io.h>
#include <cell/lang/scanner.h>
#include <cell/utf8.h>

#include "internal.h"

#define BOM             0xFEFF



void scanner_error(cell_lang_scanner * scn, int offset, const cell_byte * msg) {

}

void scanner_next(cell_lang_scanner * scn) {

}

void scanner_init(cell_lang_scanner * scn) {

}

void scanner_comment(cell_lang_scanner * scn) {

}
