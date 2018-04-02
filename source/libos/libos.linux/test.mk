include config.mk

SOURCES = \
    ctest/main.c

CINCLUDES += include

ifneq ($(ARCH),)

SOURCES += csource/$(ARCH)/start.S

TARGET=$(ARCH)/bin/os_linux_test

endif
 
all: $(TARGET)
	
include $(ROOT)/source/config/make/iter.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) --no-undefined -o $@ $^ $(ARCH)/lib/libos.linux.a
	readelf -a $@ > $(BUILDDIR)/$(notdir $@).elfdump
	$(OBJDUMP) -source $@ > $(BUILDDIR)/$(notdir $@).objdump
	@ chmod +x $(TARGET)
