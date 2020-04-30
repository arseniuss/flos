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

#ifndef __CELL__LANG_TOKEN_H__
#    define __CELL__LANG_TOKEN_H__

#    include <cell/builtin.h>

#    define TOKEN_SYSTEM 0
#    define TOKEN_LITERAL 1
#    define TOKEN_BRACKETS 2
#    define TOKEN_OPER 3
#    define TOKEN_KEYWORDS 4

enum cell_lang_token {
    CELL_LANG_TINVALID = -1,
#    define __(u, l, str)   CELL_LANG_T##u,
#    include <cell/lang/tokens.inc>
    CELL_LANG_TLAST
};

#    undef __

typedef enum cell_lang_token cell_lang_token;

extern const char *cell_lang_tokens[CELL_LANG_TLAST];

#endif /* __CELL__LANG_TOKEN_H__ */
