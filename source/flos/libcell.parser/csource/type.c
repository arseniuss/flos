/**
 *  Cell language parser library
 *  Copyright (C) 2020  Armands Arseniuss Skolmeisters
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

#include "internal.h"

void cell_lang_parser_parse_type(cell_lang_parser prs, cell_lang_ast_type ** type) {
    cell_error err;

    __debug("cell_lang_parser_parse_type\n");

    do {

        cell_lang_ast_type *t = CELL_NULL;
        if((err = cell_mem_alloc(sizeof(*t), (void **)&t)) != CELL_NULL) {
            cell_error_label_throw(prs->err_lbl, err);
            return;
        }
        __builtin_memset(t, 0, sizeof(*t));
        t->base.type = CELL_LANG_ATYPE;

        switch (prs->tok) {
            case CELL_LANG_TIDENT:
                cell_lang_parser_parse_ident(prs, &t->name);

                *type = t;
                type = &t->base_type;
                break;
            case CELL_LANG_TINT:
            case CELL_LANG_TMUL:
                if((err = cell_string_copy_s(&t->name, &prs->str))) {
                    __debug("alloc error\n");
                    cell_error_label_throw(prs->err_lbl, err);
                }

                cell_lang_parser_next(prs);

                *type = t;
                type = &t->base_type;
                break;
            case CELL_LANG_TLQBRACK:
                t->name = cell_string_c("[]");

                cell_lang_parser_next(prs);

                cell_lang_parser_parse_type(prs, &t->sub_type);

                if(prs->tok != CELL_LANG_TRQBRACK) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TRQBRACK);
                    return;
                }

                cell_lang_parser_next(prs);
                *type = t;
                type = &t->base_type;

                break;
            case CELL_LANG_TSTRUCT:
                t->name = cell_string_c("struct");
                cell_lang_parser_next(prs);
                if(prs->tok != CELL_LANG_TLCBRACK) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TLCBRACK);
                    return;
                }
                cell_lang_parser_next(prs);

                cell_lang_parser_parse_struct(prs, &t->sub_type);

                if(prs->tok != CELL_LANG_TRCBRACK) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TRCBRACK);
                    return;
                }

                cell_lang_parser_next(prs);
                *type = t;
                type = &t->base_type;

                break;
            case CELL_LANG_TINTERFACE:
                t->name = cell_string_c("interface");
                cell_lang_parser_next(prs);
                if(prs->tok != CELL_LANG_TLCBRACK) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TLCBRACK);
                    return;
                }
                cell_lang_parser_next(prs);

                cell_lang_parser_parse_inf(prs, &t->sub_type);

                if(prs->tok != CELL_LANG_TRCBRACK) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TRCBRACK);
                    return;
                }

                cell_lang_parser_next(prs);
                *type = t;
                type = &t->base_type;

                break;

                break;
            case CELL_LANG_TFUNC:
                t->name = cell_string_c("func");
                cell_lang_parser_next(prs);
                if(prs->tok != CELL_LANG_TLPAREN) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TLPAREN);
                    return;
                }
                cell_lang_parser_next(prs);

                cell_lang_parser_parse_type(prs, &t->sub_type);

                if(prs->tok != CELL_LANG_TRPAREN) {
                    cell_lang_ast_free((cell_lang_ast_node *) t);
                    cell_lang_parser_expect(prs, CELL_LANG_TRPAREN);
                    return;
                }
                cell_lang_parser_next(prs);

                cell_lang_parser_parse_type(prs, &t->base_type);

                *type = t;
                type = &t->base_type;

                break;
            case CELL_LANG_TRQBRACK:
                cell_lang_ast_free((cell_lang_ast_node *) t);
                return;
            case CELL_LANG_TNEWLINE:
            case CELL_LANG_TSEMICOLON:
            case CELL_LANG_TEOF:
                cell_lang_ast_free((cell_lang_ast_node *) t);
                return;
            default:
                cell_lang_ast_free((cell_lang_ast_node *) t);
                return;
        }



    } while(1);
}
