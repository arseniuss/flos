#
#    Cell language parser library
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

LIBRARIES = cell_parser

cell_parser_LIBS = \
	flos/libcell.ast \
	flos/libcell.builtin \
	flos/libcell.fmt \
	flos/libcell.io \
	flos/libcell.mem \
	flos/libcell.os \
	flos/libcell.scanner \
	flos/libcell.token 

cell_parser_CFLAGS = -Iinclude

cell_parser_SRCS = \
	csource/ident.c \
	csource/inf.c \
	csource/interface.c \
	csource/literal.c \
	csource/module.c \
	csource/parser.c \
	csource/struct.c \
	csource/type.c \
	csource/variable.c

cell_parser_HDRS = \
	include/cell/lang/parser.h
	
cell_parser_HAS_TESTS = 1

cell_parser_TEST_LIBS = \
    flos/libcell.ascii \
    flos/libcell.utf

cell_parser_linux_TEST_LIBS = \
    flos/libcell.linux

cell_parser_TESTS = \
    csource/tests/error_test1.c \
    csource/tests/file_tests.c \
    csource/tests/internal.c \
    csource/tests/test.c 

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_parser_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_parser_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
