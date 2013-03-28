DIRS =          \
	library \
	source  \
	tests   \

.DEFAULT_GOAL := all

.PHONY: all
all: $(DIRS)

.PHONY: clean
clean: $(DIRS)

.PHONY: do_tests
do_tests:
ifeq ($(wildcard tests/*.t), )
	$(MAKE)
endif
	@tools/do_tests

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
