SOURCES =      \
	t1.cpp \
	t2.cpp \

INCLUDE_DIR = ../include

INCLUDES =                         \
	$(INCLUDE_DIR)/field.hpp   \
	$(INCLUDE_DIR)/table.hpp   \
	$(INCLUDE_DIR)/tttbook.hpp \

LIBRARY_DIR = ../library

LIBRARY = $(LIBRARY_DIR)/libtttbook.a
	
TARGETS = $(SOURCES:.cpp=.t)

COMPILER = g++
COMPILER_FLAGS = -std=c++11 -I./ -I$(INCLUDE_DIR)

.DEFAULT_GOAL := all

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS)

%.t: %.cpp $(INCLUDES) $(LIBRARY)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $< $(LIBRARY)
