#
#    Cell language scanner library
#    Copyright (C) 2019 Armands Arseniuss Skolmeisters
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

LIBRARIES = cell_scanner

cell_scanner_CFLAGS = -Iinclude

cell_scanner_LIBS = \
	flos/libcell.ascii \
	flos/libcell.builtin \
	flos/libcell.mem \
	flos/libcell.os \
	flos/libcell.token \
	flos/libcell.utf
	
cell_scanner_linux_LIBS = \
	flos/libcell.linux

cell_scanner_HDRS = \
	include/cell/lang/position.h \
	include/cell/lang/scanner.h

cell_scanner_SRCS = \
	csource/scan.c \
	csource/scanner.c \
	csource/source.c
	
cell_scanner_HAS_TESTS = 1

cell_scanner_TEST_LIBS = \
    flos/libcell.fmt \
    flos/libcell.io

cell_scanner_TESTS = \
    csource/tests/test1.c \
    csource/tests/test2.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_scanner_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_scanner_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
