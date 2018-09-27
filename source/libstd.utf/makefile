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

NAME		= libcell_utf


include config.mk

HDRS		= \
		include/cell/utf.h

GEN_SRCS	= \
		csource/char_isalpha.c \
		csource/char_iscntrl.c \
		csource/char_isdigit.c \
		csource/char_islower.c \
		csource/char_isspace.c \
		csource/char_istitle.c \
		csource/char_isupper.c
	
SRCS		= \
		csource/chartype.c
SRCS		+= $(GEN_SRCS)

GEN		+= $(GEN_SRCS)

include scripts/libs.base.mk

data/UnicodeData.txt:
	wget -N "http://www.unicode.org/Public/zipped/$(UNICODE_VER)/UCD.zip"
	unzip -j UCD.zip 

$(GEN_SRCS): data/UnicodeData.txt
	awk -f bin/build_c.awk data/UnicodeData.txt

