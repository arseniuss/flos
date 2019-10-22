MKFILES = $(wildcard */makefile)

all:
	@ for i in $(MKFILES); do \
		make -C $$(dirname $$i) || exit 1; \
		echo $$i done; \
	done

clean:
	@ for i in $(MKFILES); do \
		make -C $$(dirname $$i) clean || exit 1; \
	done
