include config.mk

HEADERS=\
    include/os/linux/defs.h \
    include/os/linux.h

SOURCES=\
    csource/syscall.c

.PHONY: .FORCE

ifneq ($(LIBNAME)-$(ARCH),-)

CFLAGS+= \
    -fPIC \
    -g \
    -I include

SOURCES+= \
    csource/$(ARCH)/syscall.c

OBJECTS= \
    $(addprefix $(BUILDDIR)/,$(SOURCES:.c=.o))

BUILDDIR?=build/$(ARCH)
LIBS = \
    $(ARCH)/lib/$(LIBNAME).a \
    $(ARCH)/lib/$(LIBNAME).so
    
all: $(LIBS)
	
$(ARCH)/lib/%.a: $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rcs $@ $^
	
$(ARCH)/lib/%.so: $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -shared -o $@ $^
	readelf -a $@ > $(BUILDDIR)/$(notdir $@).elfdump
	$(OBJDUMP) -source $@ > $(BUILDDIR)/$(notdir $@).objdump

$(OBJECTS): $(SOURCES) $(HEADERS)

$(BUILDDIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(CC) $(CFLAGS) -c -o $@ $<
	
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
