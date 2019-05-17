#include <cell/os.h>
#include <cell/os/linux.h>

cell_error *os_close(fd_t fd) {
    long res = os_linux_sys_close(fd);

    if(res != 0) {
        return os_error[-os_linux_sys_errno];
    }

    return CELL_NULL;
}

cell_error *os_open(fd_t * fd, const cell_string file, cell_byte omode) {
    int flags = 0, mode = 0;

    flags |= omode & 0x3;              // read, write same as POSIX

    int res = os_linux_sys_open((const char *)file.buffer, flags, mode);

    if(res < 0) {
        return os_error[-os_linux_sys_errno];
    }

    return (*fd = res, CELL_NULL);
}

void os_exit(const cell_string msg) {
    os_linux_sys_write(1, msg.buffer, msg.len);

    os_linux_sys_exit(msg.len == 0 ? 0 : 1);
}

cell_error *os_write(fd_t fd, const void *buf, cell_size bytes,
                     cell_ssize * written) {
    cell_ssize res = os_linux_sys_write(fd, buf, bytes);

    if(res < 0) {
        return os_error[-os_linux_sys_errno];
    }

    if(written)
        *written = res;

    return CELL_NULL;
}

extern char edata;

cell_error *os_sbrk(cell_uint32 inc, void **ptr) {
    int res;
    static void *last_position = CELL_NULL;

    if(last_position == CELL_NULL) {

        if((res = os_linux_sys_brk(&edata)) != 0) {
            return os_error[-os_linux_sys_errno];
        }
        last_position = &edata;
    }

    void *new_addr = (void *)((cell_uintptr) last_position + inc);
    if((res = os_linux_sys_brk(new_addr)) != 0) {
        return os_error[-os_linux_sys_errno];
    }

    last_position = new_addr;

    if(ptr)
        *ptr = new_addr;

    return CELL_NULL;
}
