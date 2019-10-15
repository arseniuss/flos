#
#    Builtin library for cell language
#    Copyright (C) 2019  Armands Arseniuss Skolmeisters
#
#    This library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with this library  If not, see <https://www.gnu.org/licenses/>.

LIBRARIES = cell_builtin

cell_builtin_DISTRO = flos

cell_builtin_SRCS = \
	csource/libc.c \
	csource/memory.c \
	csource/string.c \
	csource/error.c

cell_builtin_HDRS = \
	include/cell/array.h \
	include/cell/assert.h \
	include/cell/builtin.h \
	include/cell/error.h \
	include/cell/memory.h \
	include/cell/slice.h \
	include/cell/string.h \
	include/cell/type.h

cell_builtin_CFLAGS = \
	-Iinclude


#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_builtin_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_builtin_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
