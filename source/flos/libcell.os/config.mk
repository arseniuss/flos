#
#    OS layer library
#    Copyright (C) 2019  Armands Arseniuss Skolmeisters
#
#    This library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this library  If not, see <https://www.gnu.org/licenses/>.

LIBRARIES = cell_os

cell_os_DISTRO = flos

cell_os_LIBS = \
    flos/libcell.builtin \
    flos/libcell.mem

cell_os_linux_LIBS = flos/libcell.linux

cell_os_linux_SRCS = \
	csource/linux/chdir.c \
	csource/linux/close.c \
	csource/linux/create.c \
	csource/linux/exit.c \
	csource/linux/file.c \
	csource/linux/open.c \
	csource/linux/os.S \
	csource/linux/read.c \
	csource/linux/sbrk.c \
	csource/linux/sleep.c \
	csource/linux/write.c


cell_os_HDRS = \
	include/cell/os/error.h \
	include/cell/os/file.h \
	include/cell/os/mem.h \
	include/cell/os/proc.h \
	include/cell/os/time.h


cell_os_CFLAGS = \
	-Iinclude
	
cell_os_HAS_TESTS = 1

cell_os_TEST_LIBS = \
    flos/libcell.io \
    flos/libcell.fmt \
    flos/libcell.utf \
    flos/libcell.ascii

cell_os_TESTS = \
    csource/tests/os_open_test.c \
    csource/tests/os_sbrk_test.c \
    csource/tests/os_sleep_test.c


#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_os_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_os_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
