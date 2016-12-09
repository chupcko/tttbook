INCLUDE_DIR := ../include
LIBRARY_DIR := ../library

SOURCES = $(wildcard *.cpp)
TARGET = tttbook
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.hpp) $(wildcard *.hpp)
LIBRARY = $(LIBRARY_DIR)/libtttbook.a
COMPILER = g++
COMPILER_FLAGS = -std=c++11 -I. -I$(INCLUDE_DIR)

.DEFAULT_GOAL := all
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: COMPILER_FLAGS += -g
debug: $(TARGET)


.PHONY: clean
clean:
	rm -rf $(TARGET)

.SUFFIXES:
SUFFIXES :=

%: %.cpp $(INCLUDES) $(LIBRARY)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $< $(LIBRARY)
