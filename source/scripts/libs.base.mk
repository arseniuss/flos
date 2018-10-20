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
ROOT		= /
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

AS		?= as
PP		?= cpp


DEFS		= __ARCH__=$(ARCH)

BUILDDIR	= $(ARCH)-$(OS)-$(HOST)

CFLAGS		+= $(addprefix -D,$(DEFS))
PPFLAGS		+= $(addprefix -D,$(DEFS))

ifeq ($(OS),flos)
CFLAGS		+= -target x86_64-unknown-flos-elf
CFLAGS		+= -I $(ROOT)/include 
PPFLAGS		+= -I $(ROOT)/include
	
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

# Using 2011 C ISO standard
CFLAGS		+= -std=c11

# Set byte/char to unsigned type
CFLAGS		+= -funsigned-char
endif


OBJS		= $(addprefix $(BUILDDIR)/obj/,$(SRCS:=.o))
DEPS		= $(addprefix $(BUILDDIR)/obj/,$(SRCS:=.d))
	
TARGET		= $(BUILDDIR)/lib/$(NAME).a
ifeq ($(NOSHARED),)
TARGET		+= $(BUILDDIR)/lib/$(NAME).so
endif
		
TEST		= $(BUILDDIR)/bin/test_$(NAME).elf
TEST_MAIN	= scripts/testing.main.c

LIBS		:= $(addprefix $(ROOT)/$(ARCH)/lib/,$(LIBS:=.a))

##### Compilation rules

.PHONY: all test install clean

all: $(TARGET)

ifeq ($(UNTESTABLE),)
test: $(TEST)
	$(TEST)

$(TEST): $(OBJS) $(TEST_MAIN) $(LIBS)
	@ mkdir -p $(dir $@)
	$(CC) -DCONFIG=TEST --no-undefined -o $@ $(TEST_MAIN) $(OBJS) $(LIBS)
	@ mkdir -p $(BUILDDIR)/obj/
	readelf -a $@ > $(BUILDDIR)/obj/$(notdir $@).elfdump
	objdump -x -D $@ > $(BUILDDIR)/obj/$(notdir $@).dump
else
test:
	@ echo This library is untestable!
endif
	
install: $(TARGET) $(HDRS)
	@ echo Installing $(NAME) ...
	@ mkdir -p $(ROOT)/$(ARCH)/lib
	@ cp -v $(BUILDDIR)/lib/$(NAME).a $(ROOT)/$(ARCH)/lib/$(NAME).a
ifeq ($(NOSHARED),)
	@ cp -v $(BUILDDIR)/lib/$(NAME).so $(ROOT)/$(ARCH)/lib/$(NAME).so
endif
	@ for i in $(HDRS); do \
	    mkdir -p `dirname $(ROOT)/$$i`; \
	    cp -v $$i $(ROOT)/$$i; \
	done
	@ echo Done
	
uninstall:
	@ echo Uninstalling $(NAME) ...
	@ rm -vf $(ROOT)/$(ARCH)/lib/$(NAME).a
	@ rm -vf $(ROOT)/$(ARCH)/lib/$(NAME).so
	@ for i in $(HDRS); do \
	    rm -vf $(ROOT)/$$i; \
	done
	@ echo Done
	
indent:
	./scripts/pre-commit.sh

clean:
	@ rm -rvf $(BUILDDIR) $(GEN)

$(LIBS): $(ROOT)/$(ARCH)/%.a: 
	echo $<

	
$(BUILDDIR)/lib/$(NAME).a: $(OBJS)
	@ mkdir -p $(dir $@)
	ar rcs $@ $^
ifeq ($(NOSHARED),)	
$(BUILDDIR)/lib/%.so: $(OBJS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -shared -o $@ $^
	readelf -a $@ > $(BUILDDIR)/obj/$(notdir $@).elfdump
	objdump -x -D $@ > $(BUILDDIR)/obj/$(notdir $@).dump
endif

$(BUILDDIR)/obj/%.c.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/obj/$<.E
	$(CC) $(CFLAGS) -M $< -MT $@ > $(BUILDDIR)/obj/$<.d
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(BUILDDIR)/obj/%.S.o: %.S
	@ mkdir -p $(dir $@)
	$(PP) $(PPFLAGS) $< > $@.asm
	$(PP) -M -MT $@ $(PPFLAGS) $< > $@.dep
	$(PP) $(PPFLAGS) -E $< > $@.E
	$(AS) $(ASFLAGS) -o $@ $@.asm
	objdump -x -D $(DUMPFLAGS) $@ > $@.dump
	
-include $(DEPS)
