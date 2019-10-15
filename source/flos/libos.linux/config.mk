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


LIBRARIES = os_linux

os_linux_NSHARED = 1

os_linux_LIBS = flos/libcell.builtin

os_linux_SRCS = \
	csource/crti.c \
	csource/error.c \
	csource/syscall.c

os_linux_amd64_SRCS = \
	csource/amd64/syscall.S \
	csource/amd64/start.S

os_linux_HDRS = \
	include/cell/os/linux.h \
	include/cell/os/linux/defs.h \
	include/cell/os/linux/error.h \
	include/cell/os/linux/errors.h \
	include/cell/os/linux/syscall.h


os_linux_CFLAGS = -Iinclude
os_linux_amd64_CFLAGS = 
os_linux_ASFLAGS =

os_linux_HAS_TESTS = 1
os_linux_TESTS = \
	csource/tests/os_sbrk_test.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
os_linux_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
os_linux_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)

