assert = $(if $($(1)),,$(error error: variable $(1) is not defined))

$(call assert,ARCH)
$(call assert,OS)
$(call assert,HOST)

ifeq ($(ARCH),amd64)
LLVM_ARCH=x86_64
else
$(error error: unsupported architecture: $(ARCH))
endif

ifeq ($(HOST),linux)
LLVM_HOST=linux-gnu-ubuntu-18.04
else
$(error error: unsupported host: $(HOST))
endif

VERSION=8.0.0
RC=rc3

all:

install:
	wget -nc https://prereleases.llvm.org/$(VERSION)/$(RC)/clang+llvm-$(VERSION)-$(RC)-$(LLVM_ARCH)-$(LLVM_HOST).tar.xz
	rm -rf clang+llvm-$(VERSION)-$(RC)-$(LLVM_ARCH)-$(LLVM_HOST)
	tar xf clang+llvm-$(VERSION)-$(RC)-$(LLVM_ARCH)-$(LLVM_HOST).tar.xz
	rm -rf $(ROOT)/$(ARCH)/llvm/clang+llvm-$(VERSION)
	mkdir -p $(ROOT)/$(ARCH)/llvm/clang+llvm-$(VERSION)
	cp -v -r ./clang+llvm-$(VERSION)-$(RC)-$(LLVM_ARCH)-$(LLVM_HOST)/* $(ROOT)/$(ARCH)/llvm/clang+llvm-$(VERSION)
	rm -rf ./clang+llvm-$(VERSION)-$(RC)-$(LLVM_ARCH)-$(LLVM_HOST)
	$(PKG-INSTALL) tool CC $(ROOT)/$(ARCH)/llvm/clang+llvm-$(VERSION)/bin/clang

uninstall:
	rm -rf $(ROOT)/$(ARCH)/llvm/clang+llvm-$(VERSION)
