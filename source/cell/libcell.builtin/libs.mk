CINCLUDES += include

CFLAGS += -fPIC

HEADERS += \
    include/cell/array.h \
    include/cell/builtin.h \
    include/cell/defs.h \
    include/cell/namespace.h \
    include/cell/slice.h \
    include/cell/string.h \
    include/cell/type.h

SOURCES += \
    csource/cell_slice.c \
    csource/cell_string.c \
    csource/cell_type.c \
    csource/cell_array.c

ifneq ($(ARCH),)
ifneq ($(LIBNAME),)
LIBS := \
	$(ARCH)/lib/$(LIBNAME).a \
	$(ARCH)/lib/$(LIBNAME).so
endif
endif

all: $(LIBS)
	
include $(ROOT)/source/config/make/iter.mk

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
