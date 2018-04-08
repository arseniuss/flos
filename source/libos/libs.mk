CINCLUDES += include

CFLAGS += -fPIC

HEADERS += \
    include/os.h

SOURCES += \
    csource/os.c

ifneq ($(ARCH),)
ifneq ($(LIBNAME),)
LIBS := \
	$(ARCH)/lib/$(LIBNAME).a \
	$(ARCH)/lib/$(LIBNAME).so
endif
endif

all: $(LIBS) 
	
include $(ROOT)/source/config/make/iter.mk
	
ifneq ($(ARCH),)

$(LIBS): $(OBJECTS)

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
