#!/bin/gnu/make

#
#	Standard Linux layer for cell language
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

NAME		= libcell_os_linux

include config.mk

HDRS		= \
		include/cell/os/linux/defs.h \
		include/cell/os/linux/syscall.h \
		include/cell/os/linux.h
	
SRCS		= \
		csource/$(ARCH)/syscall.S \
		csource/syscall.c 
	
ifeq ($(CONFIG), TEST)
SRCS		+= \
		csource/testing/write.c
endif
	
include scripts/libs.base.mk
	