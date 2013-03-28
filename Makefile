DIRS =          \
	library \
	source  \
	test    \

.DEFAULT_GOAL := all

.PHONY: all
all: $(DIRS)

.PHONY: clean
clean: $(DIRS)

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MAKEFLAGS) $(MAKECMDGOALS)
