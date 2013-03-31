.DEFAULT_GOAL := all
.PHONY: all
all: source- tests-

.PHONY: debug
debug: source-debug tests-debug

.PHONY: clean
clean: library-clean source-clean tests-clean

.PHONY: do_tests
do_tests: tests-clean tests-debug
	tools/do_tests

GET_DIR = $(word 1, $(subst -, , $(1)))
GET_GOAL = $(word 2, $(subst -, , $(1)))
GOALS :=               \
	library-      \
	library-debug \
	library-clean \
	source-       \
	source-debug  \
	source-clean  \
	tests-        \
	tests-debug   \
	tests-clean   \

.PHONY: $(GOALS)
$(GOALS):
	$(MAKE) -C $(call GET_DIR, $@) $(call GET_GOAL, $@)

define GENERATE_GOAL_RULES =
  $(1)-: library-
  $(1)-debug: library-debug
  $(1)-clean: library-clean
endef

$(foreach dir, source tests, $(eval $(call GENERATE_GOAL_RULES, $(dir))))
