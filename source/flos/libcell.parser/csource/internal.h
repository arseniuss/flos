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
#ifndef __CELL__INTERNAL__
#    define __CELL__INTERNAL__

#    include <cell/error.h>
#    include <cell/fmt.h>
#    include <cell/io.h>
#    include <cell/lang/parser.h>
#    include <cell/lang/position.h>
#    include <cell/lang/scanner.h>
#    include <cell/lang/token.h>
#    include <cell/mem.h>
#    include <cell/mem/string.h>
#    include <cell/slice.h>
#    include <cell/string.h>

#    define __debug(fmt, ...) cell_io_printf("%s:%d: " fmt, __FILE__,__LINE__, ##__VA_ARGS__)

cell_slice_type_def(cell_lang_parser_error, cell_lang_parser_error);

struct cell_lang_parser_s {
    cell_lang_scanner scn;

    cell_lang_token ltok, tok;
    cell_lang_range pos;
    cell_string str;

    cell_error_label err_lbl;
    cell_lang_parser_error_slice_type errors;
};

void cell_lang_parser_expect(cell_lang_parser prs, cell_lang_token tok);
void cell_lang_parser_expect_semi(cell_lang_parser prs);

void cell_lang_parser_next(cell_lang_parser prs);


cell_lang_ast_ident **cell_lang_parser_parse_ident(cell_lang_parser prs, cell_lang_ast_ident ** ident);


void cell_lang_parser_parse_module(cell_lang_parser prs, cell_lang_ast_node ** node);


#endif /* !__CELL__INTERNAL__ */
