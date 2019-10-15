


MKFILES = $(wildcard */makefile)

all:
	for i in $(MKFILES); do \
		make -C $$(dirname $$i); \
	done

clean:
	for i in $(MKFILES); do \
		make -C $$(dirname $$i) clean; \
	done
