#
#	Standard formatting for cell language
#	Copyright (c) Armands Arseniuss Skolmeisters, All rights reserved.
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

LIBRARIES = cell_fmt

cell_fmt_LIBS = \
    flos/libcell.builtin \
    flos/libcell.ascii \
    flos/libcell.utf \
    flos/libcell.os

cell_fmt_linux_LIBS = flos/libcell.linux

cell_fmt_CFLAGS = -Iinclude
cell_fmt_LDFLAGS = -z norelro

cell_fmt_SRCS = \
    csource/fmt.c

cell_fmt_HDRS = \
    include/cell/fmt.h

cell_fmt_HAS_TESTS = 1
cell_fmt_TESTS = \
    csource/tests/fmt_test.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_fmt_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_fmt_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
