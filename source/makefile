#!/bin/gnu/make

ifeq ($(ROOT),)
$(error ROOT is not defined!)
endif

DIRS = $(wildcard */makefile)
DIRS := $(DIRS:/makefile=)


MKFILES = \
	$(addsuffix /makefile,$(DIRS))

.PHONY: $(DIRS)

all:
	for i in $(DIRS); do make -C $$i all; done

uninstall:
	for i in $(DIRS); do make -C $$i uninstall || exit; done

clean:
	for i in $(DIRS); do make -C $$i clean; done


