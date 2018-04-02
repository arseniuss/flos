include config.mk

SOURCES=\
    ctest/main.c

.PHONY: .FORCE

ifneq ($(ARCH),-)

DEBUG=y

ifeq ($(DEBUG),y)
CFLAGS += -g
endif

SOURCES += ctest/$(ARCH)/start.S

CINCLUDES += include

OBJECTS= \
    $(addprefix $(BUILDDIR)/,$(SOURCES:=.o))

BUILDDIR?=build/$(ARCH)

CFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix -D,$(CDEFS))
ASFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix --defsym ,$(CDEFS))

TARGET=$(ARCH)/bin/os_linux_test
    
all: $(TARGET)
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) --no-undefined -o $@ $^ $(ARCH)/lib/libos.linux.a
	readelf -a $@ > $(BUILDDIR)/$(notdir $@).elfdump
	$(OBJDUMP) -source $@ > $(BUILDDIR)/$(notdir $@).objdump
	@ chmod +x $(TARGET)

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

else



endif

headers: $(HEADERS)
	@echo $(HEADERS)

sources:
	@echo $(SOURCES)
