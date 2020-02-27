MKFILES = $(wildcard */makefile)

all:
	@ for i in $(MKFILES); do \
		make -C $$(dirname $$i) || exit 1; \
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
