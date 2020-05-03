/**
 *  Cell language scanner library
 *  Copyright (C) 2019 Armands Arseniuss Skolmeisters
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

#include <cell/ascii.h>
#include <cell/assert.h>
#include <cell/fmt.h>
#include <cell/io.h>
#include <cell/lang/scanner.h>
#include <cell/os/proc.h>
#include <cell/slice.h>
#include <cell/string.h>

TEST(test1) {
    cell_error err;
    cell_lang_source src;
    cell_lang_scanner scn;

    if((err = cell_lang_source_new(cell_string_c("tests/test1.cell"), &src)) != CELL_NULL) {
        cell_slice_make_generic(s, 256);

        cell_fmt_format(&s, cell_string_c("lang: %S"), err->string(err));

        cell_os_exit(cell_string_s(s));
    }

    if((err = cell_lang_scanner_new(&scn, src)) != CELL_NULL) {
        cell_os_exit(err->string(err));
    }

    cell_lang_token tok;
    cell_lang_position pos;
    cell_string str;

    while((tok = cell_lang_scanner_scan(scn, &pos, &str)) > CELL_LANG_TEOF) {
        cell_io_printf("\t%s: ", cell_lang_tokens[tok]);
        if(!cell_ascii_isspace(str.buffer[0])) {
            cell_io_printf(" \"%S\"", str);
        }
        cell_io_printf("\n");
    }

    if(tok != CELL_LANG_TEOF) {
        err = cell_lang_scanner_err(scn);

        cell_io_printf("failed with char: %S", str);
        if(err != CELL_NULL) {
            cell_io_printf(" (%S)", err->string(err));
        }
        cell_io_printf("\n");
    }

    cell_io_printf(cell_string_c("DONE!"));
}
