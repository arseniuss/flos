
CFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix -D,$(CDEFS))
    
ASFLAGS += \
    $(addprefix -I,$(CINCLUDES)) \
    $(addprefix --defsym ,$(CDEFS))
    
OBJECTS += $(addprefix $(BUILDDIR)/,$(SOURCES:=.o))

DEPS += $(addprefix $(BUILDDIR)/,$(SOURCES:=.d))

-include $(DEPS)

ifneq ($(ARCH),)

BUILDDIR?=build/$(ARCH)

$(BUILDDIR)/%.c.o: %.c
	@ $(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(CC) $(CFLAGS) -M $< -MT $@ > $(BUILDDIR)/$<.d
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.S.o: %.S
	@ $(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -E $< > $(BUILDDIR)/$<.E
	$(AS) $(ASFLAGS) -c -o $@ $(BUILDDIR)/$<.E

clean:
	@ $(RM) -rfv $(BUILDDIR)/
	@ $(RM) -rvf $(ARCH)

else

BUILDDIR?=build

endif

sources:
	@ $(ECHO) $(SOURCES)

objects:
	@ $(ECHO) $(OBJECTS)

headers:
	@ $(ECHO) $(HEADERS)

libs:
	@ $(ECHO) $(LIBS)

deps:
	@ $(ECHO) $(DEPS)

