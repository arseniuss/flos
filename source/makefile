#!/bin/gnu/make

ifeq ($(ROOT),)
$(error ROOT is not defined!)
endif

DIRS = $(wildcard */makefile)


MKFILES = \
	$(addsuffix /makefile,$(DIRS))

.PHONY: $(DIRS)

all: $(DIRS)

$(DIRS): %/makefile:
	@ make -C $*

clean:
	for i in $(DIRS); do make -C $$i clean; done


