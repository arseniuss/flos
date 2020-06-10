MKFILES = $(wildcard */makefile)

all:
	@ for i in $(MKFILES); do \
		make -C $$(dirname $$i) all tests || exit 1; \
		echo $$i done; \
	done

clean:
	@ for i in $(MKFILES); do \
		make -C $$(dirname $$i) clean; \
	done

uninstall:
	@ for i in $(MKFILES); do \
		make -C $$(dirname $$i) uninstall; \
	done
