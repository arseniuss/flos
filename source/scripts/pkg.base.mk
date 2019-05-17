ifeq ($(CFG),)
$(error CFG is not set!)
endif

include $(CFG)

include /source/$(PACKAGE)/libs.mk

ifeq ($(OS),flos)   

SHELL=/bin/gnu/sh

endif

PKGPATH		= /config/pkg
PKGCFGS		= $(addsuffix .pkg.cfg,$(addprefix $(PKGPATH)/,$(LIBS)))

static_libraries:
	@ for lib in $(STATIC_LIBS); do \
	    echo -n "$$PREFIX/$$ARCH/lib/$$lib "; \
	done
	@ for cfg in $(PKGCFGS); do \
	    make --no-print-directory -f /source/scripts/pkg.base.mk static_libraries CFG="$$cfg" ;\
	done
	
dep_libraries:
ifneq ($(VERBOSE),)
	@ echo "$(PACKAGE) direct dependencies: $(LIBS) " ;
else
	@ echo -n " $(PACKAGE) $(LIBS)"
endif
	@ for cfg in $(PKGCFGS); do \
	    make --no-print-directory -f /source/scripts/pkg.base.mk dep_libraries CFG="$$cfg" ;\
	done
