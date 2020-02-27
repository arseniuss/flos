#
#	Manual memory management library for cell language
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

LIBRARIES = cell_mem

cell_mem_DISTRO = flos

cell_mem_LIBS = \
	flos/libcell.builtin \
	flos/libcell.os

cell_mem_linux_LIBS = \
	flos/libcell.linux

cell_mem_CFLAGS = \
    -Iinclude

cell_mem_SRCS = \
	csource/wrapper.c \
	csource/dlmalloc.c

cell_mem_HDRS = \
	include/cell/mem.h
	
cell_mem_HAS_TESTS = 1

cell_mem_TEST_LIBS = \
    flos/libcell.io \
    flos/libcell.fmt \
    flos/libcell.utf \
    flos/libcell.ascii

cell_mem_TESTS = \
    csource/tests/mem_alloc.c

cell_mem_TEST_CMD = \
    ulimit -v 100; ulimit -m 100; ulimit -H -v;

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_mem_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_mem_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
