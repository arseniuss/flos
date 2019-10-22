#
#    Standard file manipulation library for cell language
#    Copyright (C) 2019  Armands Arseniuss Skolmeisters
#
#    This library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with this library  If not, see <https://www.gnu.org/licenses/>.

LIBRARIES = std_file

std_file_DISTRO = flos

#
# $_BUILDDIR(1 - arch, 2 - os, 3 - host, 4 - category)
#
std_file_BUILDDIR = $(1)-$(2)-$(3)/$(4)

#
# $_INSTALLDIR(1 - arch, 2 - os, 3 - host, 4 - category, 5 - distro)
#
std_file_INSTALLDIR = $(ROOT)/$(1)/$(2)/$(4)
