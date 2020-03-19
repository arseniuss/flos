/**
 *  Cell language parser library
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

#ifndef __CELL__LANG_PARSER_H__
#    define __CELL__LANG_PARSER_H__

#    include <cell/error.h>
#    include <cell/lang/source.h>
#    include <cell/lang/ast.h>
#    include <cell/lang/scanner.h>

typedef struct cell_lang_parser_s *cell_lang_parser;

//cell_error cell_lang_parse(cell_lang_source * src, cell_lang_ast ** ast);


cell_error cell_lang_parser_new(cell_lang_parser * prs, cell_lang_scanner scn);

cell_error cell_lang_parser_parse(cell_lang_parser prs);


#endif /* __CELL__PARSER_H__ */
