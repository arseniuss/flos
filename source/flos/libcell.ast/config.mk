#
#    Cell language AST library
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

LIBRARIES = cell_ast

cell_ast_LIBS = \
	flos/libcell.builtin \
	flos/libcell.scanner \
	flos/libcell.token \
	flos/libcell.mem

cell_ast_CFLAGS = -Iinclude

cell_ast_HDRS = \
	include/cell/lang/ast.h \
	include/cell/lang/visit.h
	
cell_ast_SRCS = \
    csource/analyze.c \
    csource/ast.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_ast_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_ast_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
