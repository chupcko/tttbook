INCLUDE_DIR := ../include
TARGET := libtttbook.a

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.hpp) $(wildcard *.hpp)
COMPILER = g++
COMPILER_FLAGS = -std=c++11 -I. -I$(INCLUDE_DIR)
ARCHIVER = ar
ARCHIVER_FLAGS = csr

.DEFAULT_GOAL := all
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: COMPILER_FLAGS += -g
debug: $(TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $@ $^

.SUFFIXES:
%.o: %.cpp $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -c -o $@ $<
