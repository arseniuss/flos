 /*
  * This file is part of the libcell distribution
  * Copyright (c) 2017 Armands Arseniuss Skolmeisters
  * 
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#define __XCONCAT(a, b) a##_##b
#define __XCONCAT3(a, b, c) a##_##b##_##c

#define __stringfy(a) #a
#define __mangle(namespace, name) __XCONCAT(namespace, name)
#define __mangle3(namespace, arch, name) __XCONCAT3(namespace, arch, name)

#ifndef NAMESPACE
#    define func(name, ...) __mangle(__VA_ARGS__, __ ## name)
#    ifdef __ARCH__
#        define afunc(name, ...) __mangle(__VA_ARGS__, __ARCH__ ## _ ## name)
#    else
#        error __ARCH__ not defined!
#    endif
#else
#    define func(name) __mangle(NAMESPACE, _ ## name)
#    define efunc(namespace, name) __mangle(namespace, _ ## name)
#    ifdef __ARCH__
#        define afunc(name) __mangle3(NAMESPACE, __ARCH__, name)
#        define eafunc(namespace, name) __mangle3(namespace, __ARCH__, name)
#    else
#        error __ARCH__ not defined!
#    endif
#endif
