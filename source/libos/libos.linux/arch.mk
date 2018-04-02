include config.mk

HEADERS=\
    include/os/linux/defs.h \
    include/os/linux.h

SOURCES=\
    csource/syscall.c

.PHONY: .FORCE

ifneq ($(LIBNAME)-$(ARCH),-)

DEBUG=y

ifeq ($(DEBUG),y)
CFLAGS += -g
endif

CFLAGS+= \
    -fPIC

CINCLUDES += include

SOURCES+= \
    csource/$(ARCH)/syscall.S

OBJECTS= \
    $(addprefix $(BUILDDIR)/,$(SOURCES:=.o))

BUILDDIR?=build/$(ARCH)
LIBS = \
    $(ARCH)/lib/$(LIBNAME).a \
    $(ARCH)/lib/$(LIBNAME).so

CFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix -D,$(CDEFS))
ASFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix --defsym ,$(CDEFS))
    
all: $(LIBS)
	
$(ARCH)/lib/%.a: $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rcs $@ $^
	
$(ARCH)/lib/%.so: $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -shared --no-undefined -o $@ $^
	readelf -a $@ > $(BUILDDIR)/$(notdir $@).elfdump
	$(OBJDUMP) -source $@ > $(BUILDDIR)/$(notdir $@).objdump

$(OBJECTS): $(SOURCES) $(HEADERS)

$(BUILDDIR)/%.c.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(BUILDDIR)/%.S.o: %.S
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(AS) $(ASFLAGS) -c -o $@ $(BUILDDIR)/$<.E
	
clean:
	@rm -rfv $(BUILDDIR)
	@rm -rvf $(ARCH)
	
libs:
	@echo $(LIBS)

else



endif

headers: $(HEADERS)
	@echo $(HEADERS)

sources:
	@echo $(SOURCES)
