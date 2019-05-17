#!/bin/gnu/make

SHELL=/bin/gnu/bash

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

install:
	for i in $(DIRS); do make -C $$i install || exit; done

uninstall:
	for i in $(DIRS); do make -C $$i uninstall || exit; done

clean:
	for i in $(DIRS); do make -C $$i clean; done


