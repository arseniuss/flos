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

LIBRARIES = std_fmt

std_fmt_LIBS = \
    flos/libcell.builtin \
    flos/libstd.ascii \
    flos/libstd.utf \
    flos/libos

std_fmt_linux_LIBS = flos/libos.linux

std_fmt_CFLAGS = -Iinclude
std_fmt_LDFLAGS = -z norelro

std_fmt_SRCS = \
    csource/fmt.c

std_fmt_HDRS = \
    include/cell/std/fmt.h

std_fmt_HAS_TESTS = 1
std_fmt_TESTS = \
    csource/tests/fmt_test.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
std_fmt_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
std_fmt_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
