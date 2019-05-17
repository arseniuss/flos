#include <cell/testing.h>
#include <cell/defs.h>

int defer_var = 1;

TEST(defer_test) {

    {
        defer {
            defer_var += 1;
        };
        defer {
            defer_var *= 3;
        };
    }
    /*
     * Defer blocks should execute in FOFI order
     * defer_var = (1 * 3) + 1 = 4 not (1 + 1) * 3 = 6
     */

    assert(defer_var == 4);
}
