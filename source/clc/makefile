#!/bin/gnu/make

#
#	Cell programming language compiler
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

NAME		= celllang 

LIBS		+= \
		libcell/libcell.parser \
		libcell/libcell.token \
		libcell/libcell.scanner
	
HDRS		=

SRCS		= \
		    csource/main.c
	
LOCATION	= /$(ARCH)/$(NAME)

include /source/scripts/cmd.base.mk

