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

LIBRARIES = os

os_DISTRO = flos

os_LIBS = flos/libcell.builtin

os_linux_LIBS = flos/libos.linux

os_linux_SRCS = \
	csource/linux/os.c \
	csource/linux/os.S


os_HDRS = \
	include/cell/os_error.h \
	include/cell/os.h


os_CFLAGS = \
	-Iinclude
	
os_HAS_TESTS = 1

os_TEST_LIBS = \
    flos/libstd.io \
    flos/libstd.fmt \
    flos/libstd.utf \
    flos/libstd.ascii

os_TESTS = \
    csource/tests/os_sbrk_test.c


#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
os_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
os_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
