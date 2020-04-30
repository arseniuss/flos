#include <cell/lang/token.h>
#include <cell/io.h>

TEST(token_test1) {
    for(cell_size i = 0; i < CELL_LANG_TLAST; i++) {
        cell_io_printf("%s\n", cell_lang_tokens[i]);
    }
}
