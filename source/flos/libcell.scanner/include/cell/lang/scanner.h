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

#ifndef __CELL__LANG_SCANNER_H__
#    define __CELL__LANG_SCANNER_H__

// import cell.token

#    include <cell/error.h>
#    include <cell/lang/position.h>
#    include <cell/lang/token.h>
#    include <cell/lang/source.h>

struct cell_lang_scanner;

// type scanner
typedef struct cell_lang_scanner_s *cell_lang_scanner;

// func new(src* source) (error, scanner)
cell_error cell_lang_scanner_newl(cell_lang_scanner * scn, cell_lang_source src);


// func (scn scanner) scan() (token, position, string)
cell_lang_token cell_lang_scanner_scan(cell_lang_scanner scn, cell_lang_position * pos, cell_string * str);

#endif /* __CELL__LANG_SCANNER_H__ */
