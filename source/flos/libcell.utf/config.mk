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

LIBRARIES = cell_utf
UNICODE_VER = 12.1.0

cell_utf_LIBS = \
	flos/libcell.builtin

cell_utf_CFLAGS = -Iinclude

cell_utf_HDRS = \
	include/cell/utf8.h

cell_utf_SRCS = \
	csource/type.c \
	csource/utf8_len.c \
	csource/utf8_char_len.c \
	csource/utf8_fromchar.c \
	csource/utf8_tochar.c

cell_utf_GEN_SRCS = \
	csource/utf8_isalpha.c \
	csource/utf8_iscntrl.c \
	csource/utf8_isdigit.c \
	csource/utf8_islower.c \
	csource/utf8_isspace.c \
	csource/utf8_istitle.c \
	csource/utf8_isupper.c

cell_utf_SRCS += $(cell_utf_GEN_SRCS)

define cell_utf_GEN =

CLEAN += clean-gen

clean-gen:
	rm -f $$(cell_utf_GEN_SRCS)

data/UnicodeData.txt:
	mkdir -p data
	cd data && wget -nc "http://www.unicode.org/Public/zipped/$$(UNICODE_VER)/UCD.zip"
	cd data && unzip -j UCD.zip

$$(cell_utf_GEN_SRCS): data/UnicodeData.txt
	awk -f bin/build_c.awk data/UnicodeData.txt
endef

cell_utf_HAS_TESTS = 1

cell_utf_TESTS = csource/tests/type_test.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cell_utf_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cell_utf_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
