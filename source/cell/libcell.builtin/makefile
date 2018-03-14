ARCHES = \
    amd64 \
    arm64 \
    armel \
    armhf \
    i386 \
    mips \
    mipsel

LIBNAME=cell.builtin
INSTALLDIR=../../..

MAKEFLAGS = \
    --no-print-directory

all: $(addprefix all-,$(ARCHES))

$(addprefix all-,$(ARCHES)):
	@arch=$(patsubst all-%,%, $@); \
	make $(MAKEFLAGS) -f arch.mk all ARCH=$$arch LIBNAME=lib$(LIBNAME)
	
install: $(addprefix install-,$(ARCHES))
	@cp -v --parents  `make -f arch.mk headers` $(INSTALLDIR)/
	
$(addprefix install-,$(ARCHES)):
	@arch=$(patsubst install-%,%, $@); \
	headers=`make -f arch.mk headers ARCH=$$arch LIBNAME=lib$(LIBNAME)`; \
	mkdir -p $(INSTALLDIR)/$$arch/; \
	cp -v --parents $$headers $(INSTALLDIR); \
	libs=`make -f arch.mk libs ARCH=$$arch LIBNAME=lib$(LIBNAME)`; \
	cp -v --parents $$libs $(INSTALLDIR);

uninstall: $(addprefix uninstall-,$(ARCHES))
	@rm -fv $(addprefix $(INSTALLDIR)/,$(shell make -f arch.mk headers))
	
$(addprefix uninstall-,$(ARCHES)):
	@arch=$(patsubst uninstall-%,%, $@); \
	headers=`make -f arch.mk headers ARCH=$$arch LIBNAME=lib$(LIBNAME)`; \
	for file in $$headers; do \
	    rm -vf $(INSTALLDIR)/$$file; \
	done; \
	libs=`make -f arch.mk libs ARCH=$$arch LIBNAME=lib$(LIBNAME)`; \
	for file in $$libs; do \
	    rm -vf $(INSTALLDIR)/$$file; \
	done
	

clean: $(addprefix clean-,$(ARCHES))
	@rm -rfv build
	@rm -rfv lib
	
$(addprefix clean-,$(ARCHES)):
	@arch=$(patsubst clean-%,%, $@); \
	make -f arch.mk clean ARCH=$$arch LIBNAME=lib$(LIBNAME)
	