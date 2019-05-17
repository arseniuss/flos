#!/bin/gnu/make

#
#	Standard UTF-8 encoding library for cell language
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

NAME		= libstd/libstd.utf

LIBS		= \
		libcell/libcell.builtin

HDRS		= \
		include/cell/utf8.h

GEN_SRCS	= \
		csource/utf8_isalpha.c \
		csource/utf8_iscntrl.c \
		csource/utf8_isdigit.c \
		csource/utf8_islower.c \
		csource/utf8_isspace.c \
		csource/utf8_istitle.c \
		csource/utf8_isupper.c
	
SRCS		= \
		csource/type.c \
		csource/utf8_len.c \
		csource/utf8_tochar.c 
	
SRCS		+= $(GEN_SRCS)

GEN		+= $(GEN_SRCS)

#ifeq ($(CONFIG),TEST)
#SRCS		+= csource/testing/type.c
#LIBS		+= cell.builtin
#endif

include /source/scripts/libs.base.mk

data/UnicodeData.txt:
	wget -N "http://www.unicode.org/Public/zipped/$(UNICODE_VER)/UCD.zip"
	unzip -j UCD.zip 

$(GEN_SRCS): data/UnicodeData.txt
	awk -f bin/build_c.awk data/UnicodeData.txt

