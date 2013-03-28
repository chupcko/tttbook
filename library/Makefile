TARGET = libtttbook.a

SOURCES =         \
	field.cpp \
	table.cpp \

INCLUDE_DIR = ../include

INCLUDES =                         \
	$(INCLUDE_DIR)/field.hpp   \
	$(INCLUDE_DIR)/table.hpp   \
	$(INCLUDE_DIR)/tttbook.hpp \
	
OBJECTS = $(SOURCES:.cpp=.o)

COMPILER = g++
COMPILER_FLAGS = -std=c++11 -I./ -I$(INCLUDE_DIR)

ARCHIVER = ar
ARCHIVER_FLAGS = csr

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $@ $^

%.o: %.cpp $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -c -o $@ $<
