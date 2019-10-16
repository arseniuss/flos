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

LIBRARIES = std_io

std_io_DISTRO = flos

std_io_LIBS = \
	flos/libcell.builtin \
	flos/libos \
	flos/libstd.fmt \
	flos/libstd.io

std_io_CFLAGS = -Iinclude

std_io_HDRS = \
	include/cell/std/io.h

std_io_SRCS = \
	csource/file.c \
	csource/print.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
std_io_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
std_io_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
