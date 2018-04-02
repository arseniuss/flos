ifeq ($(ROOT),)
$(error ROOT is not defined!)
endif

ifeq ($(MKFILES),)
$(error MKFILE is not defined!)
endif

include $(ROOT)/config/make/arches.mk

ifneq ($(ARCH),)

all: $(addprefix all-,$(MKFILES))

install: $(addprefix install-,$(MKFILES))

uninstall: $(addprefix uninstall-,$(MKFILES))

clean: $(addprefix clean-,$(MKFILES))

$(addprefix all-,$(MKFILES)): all-%:
	$(MAKE) -f $* ARCH=$(ARCH) $(MKDEF-$*)

$(addprefix install-,$(MKFILES)): install-%:
	$(MAKE) -f $* install ARCH=$(ARCH) $(MKDEF-$*)
	
$(addprefix uninstall-,$(MKFILES)): uninstall-%:
	$(MAKE) -f $* uninstall ARCH=$(ARCH) $(MKDEF-$*)

$(addprefix clean-,$(MKFILES)): clean-%:
	$(MAKE) -f $* clean ARCH=$(ARCH) $(MKDEF-$*)

else

# recursive for each architecture

all: $(addprefix all-,$(ARCHES))

install: $(addprefix install-,$(ARCHES))

uninstall: $(addprefix uninstall-,$(ARCHES))

clean: $(addprefix clean-,$(ARCHES))

$(addprefix all-,$(ARCHES)): all-%:
	$(MAKE) all ARCH=$*

$(addprefix install-,$(ARCHES)): install-%:
	$(MAKE) install ARCH=$*

$(addprefix uninstall-,$(ARCHES)): uninstall-%:
	$(MAKE) uninstall ARCH=$*

$(addprefix clean-,$(ARCHES)): clean-%:
	$(MAKE) clean ARCH=$*
	
endif
	
