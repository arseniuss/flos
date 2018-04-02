include config.mk

CINCLUDES += include

CFLAGS += -fPIC

HEADERS = \
    include/os/linux/defs.h \
    include/os/linux.h

SOURCES += \
    csource/syscall.c

ifneq ($(ARCH),)

SOURCES += \
    csource/$(ARCH)/syscall.S

ifneq ($(LIBNAME),)

LIBS := \
    $(ARCH)/lib/$(LIBNAME).a \
    $(ARCH)/lib/$(LIBNAME).so

endif
endif

all: $(LIBS)

include $(ROOT)/source/config/make/defaults.mk
	
$(LIBS): $(OBJECTS)

ifneq ($(ARCH),)

$(ARCH)/lib/%.a: $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rcs $@ $^
	
$(ARCH)/lib/%.so: $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -shared --no-undefined -o $@ $^
	readelf -a $@ > $(BUILDDIR)/$(notdir $@).elfdump
	$(OBJDUMP) -source $@ > $(BUILDDIR)/$(notdir $@).objdump

$(OBJECTS): $(SOURCES) $(HEADERS)

endif
