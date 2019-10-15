#
#    Cell programming language compiler
#    Copyright (C) 2019  Armands Arseniuss Skolmeisters
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

BINARIES = cellc

cellc_DISTRO = flos

cellc_LIBS = \
	flos/libos \
	flos/libcell.builtin \
	flos/libstd.mem \
	flos/libcell.scanner \
	flos/libstd.io \
	flos/libcell.token \
	flos/libcell.ast \
	flos/libcell.parser \
	flos/libcell.ir

cellc_linux_LIBS = \
	flos/libos.linux

cellc_CFLAGS = -Iinclude

cellc_SRCS = csource/main.c

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
cellc_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
cellc_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
