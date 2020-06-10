#include <cell/linux.h>
#include <cell/string.h>

TEST(sys_write_test) {
    cell_byte str[] = "system write";

    cell_linux_sys_write(0, str, cell_c_strlen(str));
}
