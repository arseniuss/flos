#ifndef __CELL__PARSER_TESTS_INTERNAL_H__
#    define __CELL__PARSER_TESTS_INTERNAL_H__

#    include <cell/lang/ast.h>
#    include <cell/lang/parser.h>
#    include <cell/lang/visit.h>

extern const cell_lang_ast_visit_if visit;

void parse_file(const char *filename);

#endif /* !__CELL__PARSER_TESTS_INTERNAL_H__ */
