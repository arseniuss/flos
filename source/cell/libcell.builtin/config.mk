ifeq ($(ROOT),)
$(error ROOT is not defined!)
endif

include $(ROOT)/config/make/config.mk
ifneq ($(ARCH),)
include $(ROOT)/$(ARCH)/config/make/arch.mk
endif
