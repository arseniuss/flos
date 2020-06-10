#
#	I/O library for cell language
#	Copyright (c) 2018 Armands Arseniuss Skolmeisters, All rights reserved.
#
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public
#	License as published by the Free Software Foundation; either
#	version 3.0 of the License, or (at your option) any later version.
#
#	This library is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	Lesser General Public License for more details.
#
#	You should have received a copy of the GNU Lesser General Public
#	License along with this library.
#

LIBRARIES = cell_io

cell_io_DISTRO = flos

cell_io_LIBS = \
	flos/libcell.builtin \
	flos/libcell.os \
	flos/libcell.fmt \
	flos/libcell.mem \
	flos/libcell.utf \
	flos/libcell.ascii

cell_io_CFLAGS = -Iinclude

cell_io_HDRS = \
	include/cell/io.h

cell_io_SRCS = \
	csource/print.c
	
cell_io_HAS_TESTS = 1

cell_io_TEST_LIBS =

cell_io_linux_TEST_LIBS = \
    flos/libcell.linux

cell_io_TESTS = \
    csource/tests/printf.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_io_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_io_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
