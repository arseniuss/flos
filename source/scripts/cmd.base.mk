#
#	Base rules for building programs of cell language in C
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

ifeq ($(ARCH),)
$(error ARCH is not set)
endif

ifeq ($(OS),)
$(error OS is not set)
endif

ifeq ($(HOST),)
$(error HOST is not set)
endif

ifeq ($(NAME),)
$(error NAME is not set.)
endif

ifeq ($(LOCATION),)
$(error LOCATION is not set.)
endif

include /source/scripts/config.mk

AWK		?= awk
AS		?= as
CC		?= cc
LD		?= ld
PP		?= cpp

BUILDDIR	= $(ARCH)-$(OS)-$(HOST)
PKGDIR      = $(NAME)-$(ARCH)-$(CONFIG)-$(VERSION)-pkg


DEPS		+= __ARCH__=$(ARCH)

ifeq ($(OS),flos)

SHELL=/bin/gnu/sh

ifeq ($(ARCH),amd64)
CFLAGS		+= -target x86_64-unknown-flos-elf
endif

ifeq ($(ARCH),)
$(error Unrecognised architecture!)
endif

CFLAGS		+= -I /include 
PPFLAGS		+= -I /include
	
# Enable all warning
CFLAGS		+= -Wall

# Enable stack protector warnings
CFLAGS		+= -Wstack-protector

# Ignore unused attributes
CFLAGS		+= -Wno-attributes

# Assert that compilation targets a freestanding environment
CFLAGS		+= -ffreestanding
	
# Do not use the standard system startup files or libraries when linking
CFLAGS		+= -nostdlib
PPFLAGS		+= -nostdlib
	
# Do not use a so-called “red zone” for x86-64 code
CFLAGS		+= -mno-red-zone

# Do not use exceptions
CFLAGS		+= -fno-exceptions -fno-asynchronous-unwind-tables

# Using 2011 C ISO standard
CFLAGS		+= -std=c11

# Set byte/char to unsigned type
CFLAGS		+= -funsigned-char
endif

ifneq ($(DEBUG),)
# Add debugging symbols
CFLAGS		+= -g
endif

OBJS		= $(addprefix $(BUILDDIR)/obj/,$(SRCS:=.o))
CRTBEGIN_OBJ	:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ	:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
	
DEPS		= $(addprefix $(BUILDDIR)/obj/,$(SRCS:=.dep))

PKGPATH		= /config/pkg

LIBS		+= libstd/common
PKGCFGS		:= $(addsuffix .pkg.cfg,$(addprefix $(PKGPATH)/,$(LIBS)))

LIBS		+= $(foreach cfg,$(PKGCFGS),$(shell make --no-print-directory -f /source/scripts/pkg.base.mk CFG="$(cfg)" dep_libraries))

LIBPATHS	= $(addprefix /source/,$(LIBS))

LIBFILES	= $(foreach cfg,$(PKGCFGS),$(shell make --no-print-directory -f /source/scripts/pkg.base.mk CFG="$(cfg)" static_libraries))
LIBFILES	:= $(sort $(LIBFILES))

.PHONY: all install uninstall package indent clean 

all: $(BUILDDIR)/bin/$(NAME) 

#
# When installing commands (executables) package configuration must be taken 
# into account.
#
# Default formula for target address is: $PREFIX/$ARCH/$CATEGORY/$DISTRO
#   $PREFIX
#   $ARCH - architecture of machine
#   $CATEGORY - category of files
#       bin - binaries
#       config - configuration files
#       data - data files
#       docs - documentation
#       include - headers
#       lib - libraries
#       source - sources
#   $DISTRO - name of distribution and of creator. ex.
#       '' - empty, default system distribution
#       'gnu'
#       'gnu/binutils'
#
install: $(BUILDDIR)/bin/$(NAME) $(HDRS) $(ARVS) $(DEPARVS)
	@ echo Installing $(NAME) ...
	@ mkdir -p /$(ARCH)/bin
	@ cp -v $(BUILDDIR)/bin/$(NAME) /$(ARCH)/bin/$(NAME)
	@ for i in $(HDRS); do \
	    mkdir -p `dirname /$$i`; \
	    cp -v $$i /$$i; \
	done
	@ echo Done

#
# Software distribution consists from one or multiple packages. Default formula
# of package names are: $NAME-$ARCH-$CONFIG-$VERSION.pkg
#   $NAME - name of package
#   $ARCH - architecture of machine or 'shared', 'mixed'
#   $CONFIG - configuration of software: 'release', 'test' etc.
#   $VERSION - version number
#
package:
	rm -rf $(PKGDIR)
	mkdir -p $(PKGDIR)
	echo "NAME = $(NAME)" >> $(PKGDIR)/package.cfg
	echo "PREFIX = $(PREFIX)" >> $(PKGDIR)/package.cfg
	echo "ARCH = $(ARCH)" >> $(PKGDIR)/package.cfg
	echo "DISTRO = $(DISTRO)" >> $(PKGDIR)/package.cfg
	echo "CONFIG = $(CONFIG)" >> $(PKGDIR)/package.cfg
	echo "VERSION = $(VERSION)" >> $(PKGDIR)/package.cfg
	echo "LOCATION = $(LOCATION)" >> $(PKGDIR)/package.cfg
	
	
uninstall:
	

indent:
	/source/scripts/pre-commit.sh

test:
	@ echo "Nothing to test yet"

clean:
	@ rm -rvf $(BUILDDIR)
		
$(BUILDDIR)/bin/$(NAME): $(OBJS) $(PKGCFGS)
	@ echo Building $@ ...
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -T /source/scripts/cmd.ld --Map $(BUILDDIR)/tmp/$(notdir $@).map -o $@  $(OBJS) $(LIBFILES) 
	readelf -a $@ > $(BUILDDIR)/tmp/$(notdir $@).elfdump
	objdump -x -D $@ > $(BUILDDIR)/tmp/$(notdir $@).dump

$(BUILDDIR)/obj/%.c.o: %.c
	@ mkdir -p $(dir $@)
	@ mkdir -p $(dir $(BUILDDIR)/tmp/$<)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/tmp/$<.E
	$(CC) $(CFLAGS) -M $< -MT $@ > $(BUILDDIR)/tmp/$<.dep
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/obj/%.S.o: %.S
	@ mkdir -p $(dir $@)
	$(PP) $(PPFLAGS) $< > $@.asm
	$(PP) -M -MT $@ $(PPFLAGS) $< > $@.dep
	$(PP) $(PPFLAGS) -E $< > $@.E
	$(AS) $(ASFLAGS) -o $@ $@.asm
	objdump -x -D $(DUMPFLAGS) $@ > $@.dump

libpaths:
	@ echo $(LIBPATHS)

$(PKGCFGS): $(PKGPATH)/%.pkg.cfg:
	@ make -C /source/$*/ all install

-include $(DEPS)
