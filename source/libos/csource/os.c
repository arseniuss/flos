#include <cell/os.h>

extern void os_sys_exit(uint32_t code);

void os_exit(uint32_t code) {
    os_sys_exit(code);
}
