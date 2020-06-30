#
#    Cell language token library
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

LIBRARIES = cell_token

cell_token_CFLAGS = -Iinclude

cell_token_HDRS = \
	include/cell/lang/source.h \
	include/cell/lang/target.h \
	include/cell/lang/token.h \
	include/cell/lang/tokens.inc


cell_token_SRCS = \
	csource/source.c \
	csource/target.c \
	csource/tokens.c

cell_token_LIBS = \
	flos/libcell.builtin \
	flos/libcell.os \
	flos/libcell.mem \
	flos/libcell.fmt
	
cell_token_linux_LIBS = \
	flos/libcell.io \
	flos/libcell.fmt \
	flos/libcell.utf \
	flos/libcell.ascii \
	flos/libcell.linux
	
cell_token_HAS_TESTS = 1

cell_token_TESTS = \
    csource/tests/source_test.c \
    csource/tests/token_tests.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_token_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_token_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
