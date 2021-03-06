.DEFAULT_GOAL := all
.PHONY: all
all: source-

.PHONY: debug
debug: source-debug tests-debug

.PHONY: tests
tests: tests-

.PHONY: examples
examples: examples-

.PHONY: clean
clean: library-clean source-clean tests-clean examples-clean

define GENERATE_GOALS_CORE =
  GOALS += $(1)-$(2:all=)
endef
define GENERATE_GOALS =
  $(foreach goal,all debug clean,$(eval $(call GENERATE_GOALS_CORE,$(1),$(goal))))
endef
$(foreach dir,library source tests examples,$(call GENERATE_GOALS,$(dir)))

.PHONY: $(GOALS)

define GENERATE_RULES_CORE =
  $(1)-$(2:all=): library-$(2:all=)
endef
define GENERATE_RULES =
  $(foreach goal,all debug,$(eval $(call GENERATE_RULES_CORE,$(1),$(goal))))
endef
$(foreach dir,source tests,$(call GENERATE_RULES,$(dir)))

define GENERATE_RULES_CORE =
  $(1)-$(2:all=): source-$(2:all=)
endef
define GENERATE_RULES =
  $(foreach goal,all debug,$(eval $(call GENERATE_RULES_CORE,$(1),$(goal))))
endef
$(call GENERATE_RULES,examples)

GET_DIR = $(word 1,$(subst -, ,$(1)))
GET_GOAL = $(word 2,$(subst -, ,$(1)))
$(GOALS):
	$(MAKE) -C $(call GET_DIR,$@) $(call GET_GOAL,$@)
