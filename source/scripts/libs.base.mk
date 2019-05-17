#
#	Base rules for building libraries of cell language in C
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

ifeq ($(ROOT),)
ROOT		= 
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
else
LIBNAME		:= $(dir $(NAME))libcell_$(notdir $(NAME))
endif

include /source/scripts/config.mk

AS		?= as
PP		?= cpp


DEFS		= __ARCH__=$(ARCH)

BUILDDIR	= $(ARCH)-$(OS)-$(HOST)

CFLAGS		+= $(addprefix -D,$(DEFS))
PPFLAGS		+= $(addprefix -D,$(DEFS))

ifeq ($(OS),flos)

SHELL=/bin/gnu/sh

CFLAGS		+= -target x86_64-unknown-flos-elf
CFLAGS		+= -I /include 
PPFLAGS		+= -I /include
	
# Enable all warning
CFLAGS		+= -Wall

# Enable stack protector warnings
CFLAGS		+= -Wstack-protector

# Set to compile position-independent-code
CFLAGS		+= -fPIC

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

# Set byte/char to unsigned type
CFLAGS		+= -funsigned-char
endif

CFLAGS		+= -pedantic-errors -Wno-gnu -std=gnu17

OBJS		= $(addprefix $(BUILDDIR)/obj/,$(SRCS:=.o))
DEPS		= $(addprefix $(BUILDDIR)/obj/,$(SRCS:=.dep))

ifneq ($(OBJS),)	

TARGET		= $(BUILDDIR)/lib/$(LIBNAME).sa
ifeq ($(NOSHARED),)
TARGET		+= $(BUILDDIR)/lib/$(LIBNAME).so
endif # ifeq ($(NOSHARED),)
endif # ifneq ($(OBJS),)

PKGPATH		= /config/pkg

LIBPATHS	= $(addprefix /source/,$(LIBS))
PKGCFGS		= $(addsuffix .pkg.cfg,$(addprefix $(PKGPATH)/,$(LIBS)))

##### Compilation rules

.PHONY: all install clean

all: $(PKGCFGS) $(TARGET)

install: $(TARGET) $(HDRS)
	@ echo Installing $(NAME) ...
	@ mkdir -p $(dir $(ROOT)/$(ARCH)/lib/$(LIBNAME))
	@ mkdir -p $(dir $(PKGPATH)/$(NAME).pkg.cfg)
	@ echo PACKAGE=$(NAME) > $(PKGPATH)/$(NAME).pkg.cfg
	@ echo ARCH=$(ARCH) >> $(PKGPATH)/$(NAME).pkg.cfg
	@ echo PREFIX= >> $(PKGPATH)/$(NAME).pkg.cfg
ifneq ($(OBJS),)
	@ cp -v $(BUILDDIR)/lib/$(LIBNAME).sa /$(ARCH)/lib/$(LIBNAME).sa
	@ echo STATIC_LIBS=$(LIBNAME).sa >> $(PKGPATH)/$(NAME).pkg.cfg
ifeq ($(NOSHARED),)
	@ cp -v $(BUILDDIR)/lib/$(LIBNAME).so $(ROOT)/$(ARCH)/lib/$(LIBNAME).so
	@ echo SHARED_LIBS=$(LIBNAME).so>> $(PKGPATH)/$(NAME).pkg.cfg
endif # ifeq ($(NOSHARED),)
endif # ifneq ($(OBJS),)
	@ echo Installing headers ...
	@ for i in $(HDRS); do \
	    mkdir -p `dirname $(ROOT)/$$i`; \
	    rm $(ROOT)/$$i; \
	    cp -v $$i $(ROOT)/$$i; \
	    chmod oug-wx $(ROOT)/$$i; \
	done
	
	
	
	@ echo Done
	
uninstall:
	@ echo Uninstalling $(NAME) ...
	@-rm -vf /$(ARCH)/lib/$(LIBNAME).sa
	@-rm -vf /$(ARCH)/lib/$(LIBNAME).so
	@-for i in $(HDRS); do \
	    echo Removing $$i;\
	    rm -vf $(ROOT)/$$i; \
	done
	@-rm $(PKGPATH)/$(NAME).pkg.cfg
	@ echo Done
	
indent:
	$(ROOT)/source/scripts/pre-commit.sh

clean:
	@-rm -rvf $(BUILDDIR) $(GEN)
	
deplibs:
	@ echo $(DEPARVS)

libpaths:
	@ echo $(LIBPATHS)

pkgs:
	echo $(PKGCFGS)

$(PKGCFGS): $(PKGPATH)/%.pkg.cfg: 
	@ make -C /source/$*/ clean 
	@ make -C /source/$*/ all install

$(BUILDDIR)/lib/$(LIBNAME).sa: $(OBJS)
	mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -r -o $@ $^
	mkdir -p $(BUILDDIR)/tmp/
	readelf -a $@ > $(BUILDDIR)/tmp/$(notdir $@).elfdump
	$(OBJDUMP) -x -D $@ > $(BUILDDIR)/tmp/$(notdir $@).dump
	
ifeq ($(NOSHARED),)	
$(BUILDDIR)/lib/%.so: $(OBJS)
	mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -shared -o $@ $^
	mkdir -p $(BUILDDIR)/tmp/
	readelf -a $@ > $(BUILDDIR)/tmp/$(notdir $@).elfdump
	$(OBJDUMP) -x -D $@ > $(BUILDDIR)/tmp/$(notdir $@).dump
endif # ifeq ($(NOSHARED),)

$(BUILDDIR)/obj/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/obj/$<.E
	$(CC) $(CFLAGS) -M $< -MT $@ > $(BUILDDIR)/obj/$<.dep
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(BUILDDIR)/obj/%.S.o: %.S
	mkdir -p $(dir $@)
	$(PP) $(PPFLAGS) $< > $@.asm
	$(PP) -M -MT $@ $(PPFLAGS) $< > $@.dep
	$(PP) $(PPFLAGS) -E $< > $@.E
	$(AS) $(ASFLAGS) -o $@ $@.asm
	$(OBJDUMP) -x -D $(DUMPFLAGS) $@ > $@.dump
	
-include $(DEPS)
