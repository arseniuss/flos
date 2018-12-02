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

ifeq ($(ROOT),)
ROOT		    = /
endif

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

AWK		?= awk
AS		?= as
CC		?= cc
LD		?= ld
PP		?= cpp

BUILDDIR	= $(ARCH)-$(OS)-$(HOST)

DEPS		+= __ARCH__=$(ARCH)

ifeq ($(OS),flos)

ifeq ($(ARCH),amd64)
CFLAGS		+= -target x86_64-unknown-flos-elf
endif

ifeq ($(ARCH),)
$(error Unrecognised architecture!)
endif

CFLAGS		+= -I $(ROOT)/include 
PPFLAGS		+= -I $(ROOT)/include
	
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
LIBS		+= std
	
DEPARVS		= $(sort $(foreach lib,$(LIBS),$(shell $(MAKE) -s -C $(ROOT)/source/lib$(lib) libs)))
ARVS		= $(addprefix $(ROOT)/$(ARCH)/lib/libcell_,$(LIBS:=.a))
	
##### Compilation rules

.PHONY: all

all: $(BUILDDIR)/bin/$(NAME)
	
install: $(BUILDDIR)/bin/$(NAME) $(HDRS) $(ARVS) $(DEPARVS)
	@ echo Installing $(NAME) ...
	@ mkdir -p $(ROOT)/$(ARCH)/bin
	@ cp -v $(BUILDDIR)/bin/$(NAME) $(ROOT)/$(ARCH)/bin/$(NAME)
	@ for i in $(HDRS); do \
	    mkdir -p `dirname $(ROOT)/$$i`; \
	    cp -v $$i $(ROOT)/$$i; \
	done
	@ echo Done
	
uninstall:
	

indent:
	./scripts/pre-commit.sh

test:
	@ echo "Nothing to test yet"

clean:
	@ rm -rvf $(BUILDDIR)
	
libs:
	@ echo  $(ARVS) $(DEPARVS)

	
$(BUILDDIR)/bin/$(NAME): $(OBJS) $(ARVS) $(DEPARVS)
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -print-file-name=crtbegin.o
	$(CC) $(CFLAGS) -print-file-name=crtend.o
	$(LD) $(LDFLAGS) -T scripts/cmd.ld -o $@ $(OBJS) $(ARVS) $(DEPARVS)
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

 $(ARVS) $(DEPARVS): $(ROOT)/$(ARCH)/lib/libcell_%.a: $(ROOT)/source/lib%/
	@ make -C $< install

-include $(DEPS)