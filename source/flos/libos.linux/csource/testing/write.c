/**
 *  Linux layer library
 *  Copyright (C) 2018 - 2019  Armands Arseniuss Skolmeisters
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

#include <cell/testing.h>
#include <cell/os/linux.h>

TEST(write) {
    ssize_t len = os_linux_sys_write(1, "TEST!\n", 7);

    assert(len > 0);
}

TEST(write_file) {
    int fd = os_linux_sys_open("test.test", O_CREAT | O_WRONLY, 0777);

    assert(fd != -1);

    ssize_t sz = os_linux_sys_write(fd, "TEST", 4);

    assert(sz == 4);

    os_linux_sys_close(fd);
}
