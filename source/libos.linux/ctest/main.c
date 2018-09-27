#include <os/linux.h>

#ifdef NAMESPACE
#    undef NAMESPACE
#endif
#define NAMESPACE os_linux_test
#include <cell/namespace.h>

void func(main) () {
    sfunc(write) (1, "Hello, world!\0", 14);
}
