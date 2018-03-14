include config.mk

INSTALLDIR?=../../..

HEADERS= \
    include/cell/array.h \
    include/cell/builtin.h \
    include/cell/defs.h \
    include/cell/namespace.inc \
    include/cell/slice.h \
    include/cell/string.h \
    include/cell/type.h

SOURCES= \
    csource/cell_slice.c \
    csource/cell_string.c \
    csource/cell_type.c \
    csource/cell_array.c


LDFLAGS = 

.PHONY: .FORCE

ifneq ($(LIBNAME)-$(ARCH),-)

include $(ROOT)/$(ARCH)/config/make/arch.mk

CFLAGS+= \
    -fPIC \
    -I include

OBJECTS= \
    $(addprefix $(BUILDDIR)/,$(SOURCES:.c=.o))

BUILDDIR?=build/$(ARCH)
LIBS = \
    $(ARCH)/lib/$(LIBNAME).a \
    $(ARCH)/lib/$(LIBNAME).so
    
GENHEADERS=\
	$(ARCH)/include/cell/arch.h


all: $(LIBS) $(GENHEADERS)
	
$(ARCH)/lib/%.a: $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rcs $@ $^
	
$(ARCH)/lib/%.so: $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -shared -o $@ $^
	readelf -a $@ > $(BUILDDIR)/$(notdir $@).elfdump

$(OBJECTS): $(SOURCES) $(HEADERS)

$(BUILDDIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

libs:
	@echo $(LIBS)
	
clean:
	@rm -rfv $(BUILDDIR)
	@rm -rvf $(ARCH)

$(GENHEADERS):
	@mkdir -p $(@D)
	@touch $@

headers: 
	@echo $(GENHEADERS)

else

headers: $(HEADERS)
	@echo $(HEADERS)

endif

	

