#include <cell/os.h>
#include <cell/os/linux.h>


error os_close(fd_t fd) {
    long res = os_linux_sys_close(fd);

    if(res != 0) {
        return os_error[-os_linux_sys_errno];
    }

    return NULL;
}
