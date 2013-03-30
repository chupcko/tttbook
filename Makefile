DIRS =          \
	library \
	source  \
	tests   \

.DEFAULT_GOAL := all
.PHONY: all
all: $(DIRS)

.PHONY: debug
debug: $(DIRS)

.PHONY: clean
clean: $(DIRS)

.PHONY: do_tests
do_tests:
	$(MAKE) debug
	@tools/do_tests

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
