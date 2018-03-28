ifeq ($(ROOT),)
$(error ROOT is not defined!)
endif

include $(ROOT)/config/make/arches.mk

LIBNAME=os.linux
INSTALLDIR?=$(ROOT)
#MAKEFLAGS = \
#	--no-print-directory

ifneq ($(ARCH),)

all: all-$(ARCH)
	
install: install-$(ARCH)
	@cp -v --parents $(shell make $(MAKEFLAGS) -f arch.mk headers ARCH= LIBNAME=) $(INSTALLDIR)/	
	
uninstall: uninstall-$(ARCH)
	@rm -fv $(addprefix $(INSTALLDIR)/,$(shell make $(MAKEFLAGS)  -f arch.mk headers ARCH= LIBNAME= ))
	@rm -fv $(addprefix $(INSTALLDIR)/,$(shell make $(MAKEFLAGS)  -f arch.mk libs ARCH= LIBNAME= ))
	
clean: clean-$(ARCH)
	@rm -rfv build
	@rm -rfv lib
	
else

all: everything
	
clean: clean-everything

endif

everything: $(addprefix all-,$(ARCHES))

$(addprefix all-,$(ARCHES)):all-%:
	make $(MAKEFLAGS) -f arch.mk all ARCH=$* LIBNAME=lib$(LIBNAME)

install-everyting: install $(addprefix install-,$(ARCHES))

$(addprefix install-,$(ARCHES)):install-%:
	@echo Installing $* ...
	@cp -v --parents $(shell make $(MAKEFLAGS) -f arch.mk headers ARCH=$* LIBNAME=lib$(LIBNAME)) $(INSTALLDIR)/
	@cp -v --parents $(shell make $(MAKEFLAGS) -f arch.mk libs ARCH=$* LIBNAME=lib$(LIBNAME)) $(INSTALLDIR)/



uninstall-everyting: uninstall $(addprefix uninstall-,$(ARCHES))

$(addprefix uninstall-,$(ARCHES)):uninstall-%:
	@rm -vf $(addprefix $(ROOT)/, $(shell make $(MAKEFLAGS)  -f arch.mk headers ARCH=$* LIBNAME=lib$(LIBNAME)))
	@rm -vf $(addprefix $(ROOT)/, $(shell make $(MAKEFLAGS)  -f arch.mk libs ARCH=$* LIBNAME=lib$(LIBNAME)))

clean-everything: $(addprefix clean-,$(ARCHES))

$(addprefix clean-,$(ARCHES)):clean-%:
	@make $(MAKEFLAGS) -f arch.mk clean ARCH=$* LIBNAME=lib$(LIBNAME)

