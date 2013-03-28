DIRS =          \
	library \
	source  \
	tests   \

.DEFAULT_GOAL := all

.PHONY: all
all: $(DIRS)

.PHONY: clean
clean: $(DIRS)

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MAKEFLAGS) $(MAKECMDGOALS)
