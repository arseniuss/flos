#
#    Linux layer library
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


LIBRARIES = cell_linux

cell_linux_NSHARED = 1

cell_linux_LIBS = \
	flos/libcell.builtin \
	flos/libcell.mem

cell_linux_SRCS = \
	csource/crti.c \
	csource/error.c \
	csource/syscall.c

cell_linux_amd64_SRCS = \
	csource/amd64/syscall.S \
	csource/amd64/start.S

cell_linux_HDRS = \
	include/cell/linux/amd64/syscalls.inc.h \
	include/cell/linux/defs.h \
	include/cell/linux/error.h \
	include/cell/linux/errors.h \
	include/cell/linux/syscall.h \
	include/cell/linux.h


cell_linux_CFLAGS = -Iinclude
cell_linux_amd64_CFLAGS = 
cell_linux_ASFLAGS =

cell_linux_HAS_TESTS = 1

cell_linux_TEST_LIBS = \
    flos/libcell.fmt \
    flos/libcell.io \
    flos/libcell.os \
    flos/libcell.utf \
    flos/libcell.ascii

cell_linux_TESTS = \
	csource/tests/sys_brk.c \
	csource/tests/sys_write.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_linux_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_linux_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)

