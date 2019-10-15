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

LIBRARIES = std_mem

std_mem_DISTRO = flos

std_mem_LIBS = \
	flos/libcell.builtin \
	flos/libos

std_mem_linux_LIBS = \
	flos/libos.linux 

std_mem_CFLAGS = \
    -Iinclude

std_mem_SRCS = \
	csource/mem.c

std_mem_HDRS = \
	include/cell/std/memory.h

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
std_mem_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
std_mem_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
