#include <cell/lang/token.h>
#include <cell/io.h>
#include <cell/lang/source.h>
#include <cell/lang/scanner.h>
#include <cell/ascii.h>

struct {
    char *text;
    cell_lang_token seq[10];
} __test_cases[] = {
    {
        .text = "var a int",.seq = {
    CELL_LANG_TVAR, CELL_LANG_TIDENT, CELL_LANG_TIDENT, 0}}
};

TEST(test2) {
    cell_io_printf("TEST2\n");

    cell_lang_source src;
    cell_error err;
    cell_lang_scanner scn;

    for(cell_size i = 0; i < sizeof(__test_cases) / sizeof(__test_cases[0]); i++) {
        cell_io_printf("\tcase %d\n", i + 1);

        if((err = cell_lang_source_string(cell_string_c(__test_cases[i].text), &src)) != CELL_NULL) {
            cell_io_printf("string source error: %S\n", err->string(err));
            return;
        }

        if((err = cell_lang_scanner_new(&scn, src)) != CELL_NULL) {
            cell_io_printf("scanner new error: %S\n", err->string(err));
            return;
        }



        cell_lang_token tok;
        cell_lang_position pos;
        cell_string str;

        for(int j = 0; j < 10; j++) {
            tok = cell_lang_scanner_scan(scn, &pos, &str);

            cell_io_printf("\t%s: ", cell_lang_tokens[tok]);
            if(!cell_ascii_isspace(str.buffer[0])) {
                cell_io_printf(" \"%S\"", str);
            }

            if(tok != __test_cases[i].seq[j]) {
                cell_io_printf(" - incorrect token\n");
                return;
            }
        }
    }

    cell_io_printf("TEST2 - done\n");
}
