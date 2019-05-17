#!/bin/gnu/make

#
#	Builtin library for cell language
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

NAME		= libcell/libcell.builtin

SRCS		= \
		csource/libc.c \
		csource/memory.c \
		csource/string.c \
		csource/error.c

HDRS		+= \
		include/cell/array.h \
		include/cell/assert.h \
		include/cell/builtin.h \
		include/cell/error.h \
		include/cell/memory.h \
		include/cell/slice.h \
		include/cell/string.h \
		include/cell/type.h

TEST_SRCS	+= \
		csource/testing/defer.c \
		csource/testing/string.c

include /source/scripts/libs.base.mk


