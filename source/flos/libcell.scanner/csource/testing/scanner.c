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


#include <cell/lang/scanner.h>
#include <cell/lang/token.h>
#include <cell/std/io.h>
#include <cell/log.h>

TEST(scanner) {
    file f;

    // Opens file in reading mode
    if((error err =
        file_open(&f, string_c("tests/test1.cell"), file_READ)) != NULL) {
        log_fatal(err);                // TODO: _Generic
    }
    defer( {
          file_close(&f);}
    );

    scn_source src;

    // Creates interface to read source file
    if((error err = scn_source_init(&src, f)) != NULL)  // TODO: _Generic
        log_fatal(err);
    defer( {
          scn_source_close(&src);}
    )

    scn *s = scn_init(&src, NULL, scn_DontInsertSemi);
    defer( {
          scn_fini(s);}
    )

        for(;;) {
        pos pos;
        string lit;

        token t = scn_scan(s, &pos, &lit);

        if(t == TOKEN_EOF) {
            break;
        }
        // TODO: position_string = ({ alloca, pos_str(&})
        log_info("%s: %s %s\n", token_string(t), position_string(pos), lit);
    }
}

TEST(scanner) {
    string s = string_c("(-b + sqrt(b**2 - 4*a*c))/(2*a)");
    scn_source src;

    if((error err = scn_source_init(&src, s)) != NULL)
        log_fatal(err);

    for(;;) {
        token t = scn_scan(s, &pos, &lit);

        if(t == TOKEN_EOF) {
            break;
        }
        // TODO: position_string = ({ alloca, pos_str(&})
        log_info("%s: %s %s\n", token_string(t), position_string(pos), lit);
    }

}
