

#
# function(1:PREFIX,2:ARCH,3:CATEGORY,4:DISTRO)
#
ifndef GET_INSTALL_LOC
$(error error: configuration variable is not defined: GET_INSTALL_LOC)
endif

#
# function(1:PREFIX,2:ARCH,3:CATEGORY,4:DISTRO)
#
ifndef GET_BUILD_LOC
$(error error: configuration variable is not defined: GET_BUILD_LOC)
endif

#
# When installing commands (executables) package configuration must be taken 
# into account.
#
# Default formula for target address is: $PREFIX/$ARCH/$CATEGORY/$DISTRO
#   $PREFIX
#   $ARCH - architecture of machine
#   $CATEGORY - category of files
#       bin - binaries
#       config - configuration files
#       data - data files
#       docs - documentation
#       include - headers
#       lib - libraries
#       source - sources
#   $DISTRO - name of distribution and of creator. ex.
#       'gnu'
#       'gnu/binutils'
#

VERSION		?= unversioned
CONFIG		=

PKGCFG_DIR	= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),config/flos/pkg,)
PKGCFG		= $(PKGCFG_DIR)/$(DISTRO)-$(NAME)-$(VERSION).pkg.cfg

BINDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),bin,$(DISTRO))
SCRDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),bin,$(DISTRO))
CFGDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),config,$(DISTRO))
DOCDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),docs,$(DISTRO))
DATADIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),data,$(DISTRO))
HDRDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),include,$(DISTRO))
LIBDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),libs,$(DISTRO))
SRCDIR		= $(call GET_INSTALL_LOC,$(PREFIX),$(ARCH),source,$(DISTRO))

define config = 
@ echo DISTRO = $(DISTRO)
@ echo NAME = $(NAME)
@ echo VERSION = $(VERSION)
@ echo CONFIG = $(CONFIG)
@ echo ARCH = $(ARCH)
@ echo "#"
@ echo "# function(1:PREFIX,2:ARCH,3:CATEGORY,4:DISTRO)"
@ echo "#"
@ echo GET_INSTALL_LOC = $(call GET_INSTALL_LOC,$$\(1\),$$\(2\),$$\(3\),$$\(4\))
endef

define redefine_BINARIES =
BINARIES_$(1)=$$(BINARIES)
endef

$(foreach arch,$(ARCH),$(eval $(call redefine_BINARIES,$(arch))))

#
# func install_target(1: arch, 2:name, 3:list, 4:directory)
#
define __install_target = 
if [ ! -z "$(3)" ]; then\
	echo "Installing $(DISTRO)/$(NAME) $(2) $(if $(1),for $(1)) ..."; \
	for i in "$(3)"; do \
		SOURCE=$(call GET_BUILD_LOC,$(PREFIX),$(1),$(4),$(DISTRO))/$$i; \
		TARGET=$(call GET_INSTALL_LOC,$(PREFIX),$(1),$(4),$(DISTRO)); \
		mkdir -p `dirname $$TARGET/$$i`; \
		cp -v $$SOURCE $$TARGET/; \
	done; \
	echo "Done installing $(2)"; \
fi

endef

define install_arch_target = 
@ $(foreach arch,$(ARCH),\
	$(call __install_target,$(arch),$(1),$($(2)_$(arch)),$(3)))
endef

define install_target =
@ $(call __install_target,,$(1),$($(2)),$(3))
endef

.PHONY: install info

INST_DEPS	= \
		$(BINARIES) \
		$(SCRIPTS) \
		$(DATA) \
		$(DOCS) \
		$(HDRS) \
		$(LIBS)

install:
	$(call install_arch_target,binaries,BINARIES,bin)
	$(call install_target,scripts,SCRIPTS,bin)
	$(call install_target,configuration,CONFIGS,config)
	$(call install_target,data,DATA,data)
	$(call install_target,documentation,DOCS,docs)
	$(call install_target,headers,HDRS,include)
	$(call install_target,libraries,LIBS,libs)

config:
	$(config)

info:
	@ echo PKG CONFIG=$(PKGCFG)
	@ echo BINARIES=$(BINDIR)
	@ echo $(foreach arch,$(ARCH),$(BINARIES_$(arch)))
	@ echo SCRIPTS=$(SCRDIR)
	@ echo CONFIGS=$(CFGDIR)
	@ echo DOCS=$(DOCDIR)
	@ echo DATA=$(DATADIR)
	@ echo INCLUDE=$(HDRDIR)
	@ echo LIBARIES=$(LIBDIR)
