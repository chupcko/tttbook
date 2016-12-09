INCLUDE_DIR := ../include
LIBRARY_DIR := ../library

SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=.t)
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.hpp) $(wildcard *.hpp)
LIBRARY = $(LIBRARY_DIR)/libtttbook.a
COMPILER = g++
COMPILER_FLAGS = -std=c++11 -I. -I$(INCLUDE_DIR)

.DEFAULT_GOAL := all
.PHONY: all
all: $(TARGETS)

.PHONY: debug
debug: COMPILER_FLAGS += -g
debug: $(TARGETS)


.PHONY: clean
clean:
	rm -rf $(TARGETS)

.SUFFIXES:
%.t: %.cpp $(INCLUDES) $(LIBRARY)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $< $(LIBRARY)
