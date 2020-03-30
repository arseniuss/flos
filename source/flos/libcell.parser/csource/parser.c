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

#include <cell/lang/ast.h>
#include <cell/lang/parser.h>
#include <cell/lang/scanner.h>
#include <cell/mem.h>

typedef struct {
    cell_lang_position pos;
    cell_string msg;
} cell_lang_parser_error;

struct cell_lang_parser_s {
    cell_lang_scanner scn;

    cell_lang_token tok;
    cell_lang_position pos;
    cell_string str;

      cell_array(cell_lang_parser_error) errors;
};

// func new(scn scanner) (error, parser)

cell_error cell_lang_parser_new(cell_lang_parser * prs, cell_lang_scanner scn) {
    cell_error err;
    cell_lang_parser p;

    if((err = cell_mem_alloc(sizeof(struct cell_lang_parser_s), (void **)&p)) != CELL_NULL)
        return err;

    p->scn = scn;
    p->tok = CELL_LANG_TINVALID;
    cell_lang_position_init(&p->pos);
    cell_string_init(&p->str);


    *prs = p;

    return CELL_NULL;
}

void cell_lang_parser_next(cell_lang_parser prs) {
    prs->tok = cell_lang_scanner_scan(prs->scn, &prs->pos, &prs->str);
}

void cell_lang_parser_expected(cell_lang_parser prs, cell_lang_position pos, cell_lang_token tok) {
    //TODO: add to error list


}

cell_lang_position cell_lang_parser_expect(cell_lang_parser prs, cell_lang_token tok) {
    cell_lang_position pos = prs->pos;

    if(prs->tok != tok) {
        cell_lang_parser_expected(prs, pos, tok);
    }

    cell_lang_parser_next(prs);

    return pos;
}

void cell_lang_parser_expect_semi(cell_lang_parser prs) {
    if(prs->tok != CELL_LANG_TRPAREM && prs->tok != CELL_LANG_TRCBRACK) {
        switch (prs->tok) {
            case CELL_LANG_TCOMMA:
                cell_lang_parser_expected(prs, prs->pos, CELL_LANG_TSEMICOLON);
            case CELL_LANG_TSEMICOLON:
                cell_lang_parser_next(prs);
                break;
            default:
                cell_lang_parser_expected(prs, prs->pos, CELL_LANG_TSEMICOLON);
                // TODO: goto statement end
                break;
        }
    }
}

cell_error cell_lang_parser_parse_ident(cell_lang_parser prs, cell_lang_ast_ident ** ident) {
    if(prs->tok != CELL_LANG_TIDENT) {
        cell_lang_parser_expect(prs, CELL_LANG_TIDENT);
    } else {
        cell_error err;

        if((err = cell_mem_alloc(sizeof(cell_lang_ast_ident), (void **)ident)))
            return err;

        cell_string_copy(&((*ident)->name), &prs->str);
        CELL_MEM_COPY(prs->pos, (*ident)->node.start);

        cell_lang_parser_next(prs);
    }

    return CELL_NULL;
}

cell_error cell_lang_parser_parse(cell_lang_parser prs) {
    cell_error err;

    cell_lang_parser_expect(prs, CELL_LANG_TMODULE);

    cell_lang_ast_node *module_path = CELL_NULL;
    cell_lang_ast_ident *ident;

    if((err = cell_lang_parser_parse_ident(prs, &ident)) != CELL_NULL)
        return err;

    module_path = &ident->node;

    while(prs->tok == CELL_LANG_TPERIOD) {
        cell_lang_parser_next(prs);

        if(prs->tok != CELL_LANG_TIDENT)
            break;

        if((err = cell_lang_parser_parse_ident(prs, &ident)) != CELL_NULL)
            return err;

        ident->node.next = module_path;
        module_path = &ident->node;
    }

    cell_lang_parser_expect_semi(prs);

    return CELL_NULL;
}
