#
#	Standard ASCII encoding library for cell language
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
#

LIBRARIES = std_ascii

std_ascii_CFLAGS = -Iinclude

std_ascii_LIBS = \
    flos/libcell.builtin

std_ascii_HDRS = \
    include/cell/ascii.h

std_ascii_SRCS = \
    csource/ascii.c


#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
std_ascii_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
std_ascii_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
