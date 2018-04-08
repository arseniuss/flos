include $(ROOT)/config/make/config.mk

OBJECTS += $(addprefix $(BUILDDIR)/,$(SOURCES:=.o))

DEPS += $(addprefix $(BUILDDIR)/,$(SOURCES:=.d))

INSTALLDIR ?= $(ROOT)

INSTALLS := $(LIBS) $(HEADERS)

-include $(DEPS)

ifneq ($(ARCH),)

include $(ROOT)/$(ARCH)/config/make/arch.mk

CFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix -D,$(CDEFS))
    
ASFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix --defsym ,$(CDEFS))

BUILDDIR ?= build/$(ARCH)

$(BUILDDIR)/%.c.o: %.c
	@ $(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(CC) $(CFLAGS) -M $< -MT $@ > $(BUILDDIR)/$<.d
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.S.o: %.S
	@ $(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(AS) $(ASFLAGS) -c -o $@ $(BUILDDIR)/$<.E

install: $(addprefix $(INSTALLDIR)/,$(INSTALLS))


$(addprefix $(INSTALLDIR)/,$(INSTALLS)): $(INSTALLDIR)/%: %
	@ $(MKDIR) -p $(dir $*)
	@ cp -v --parents $* $(INSTALLDIR)/

uninstall:
	@ cd $(INSTALLDIR)/; rm -fv $(INSTALLS)

clean:
	@ $(RM) -rfv $(BUILDDIR)/
	@ $(RM) -rvf $(ARCH)

else

BUILDDIR?=build

clean:
	@ $(RM) -rvf $(BUILDDIR)/

endif

sources:
	@ $(ECHO) $(SOURCES)

objects:
	@ $(ECHO) $(OBJECTS)

headers:
	@ $(ECHO) $(HEADERS)

libs:
	@ $(ECHO) $(LIBS)

installs:
	@ $(ECHO) $(INSTALLS)

deps:
	@ $(ECHO) $(DEPS)

