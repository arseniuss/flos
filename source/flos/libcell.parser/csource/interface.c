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

#include <cell/lang/parser.h>
#include <cell/lang/scanner.h>
#include <cell/lang/source.h>

cell_error cell_lang_parse(cell_lang_source * src, cell_lang_ast_node ** ast) {
    cell_error err;
    cell_lang_scanner scn;

    if((err = cell_lang_scanner_new(&scn, *src)) != CELL_NULL)
        return err;

    cell_lang_parser prs;

    if((err = cell_lang_parser_new(&prs, scn)) != CELL_NULL)
        return err;

    if((err = cell_lang_parser_parse(prs, ast)) != CELL_NULL)
        return err;

    return CELL_NULL;
}
