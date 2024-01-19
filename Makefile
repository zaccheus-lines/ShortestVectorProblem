# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -Ofast

# Debug flags
DEBUG_CXXFLAGS = -Wall -Werror -std=c++20 -O0 -g

# Source files
SOURCES = src/main.cpp src/vector.cpp src/lattice.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: runme

# Rule to create the runme executable (optimized)
runme: $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o runme $(OBJECTS)

# Rule to create the debug version of runme
debug: $(OBJECTS)
		$(CXX) $(DEBUG_CXXFLAGS) -o runme_debug $(OBJECTS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile .cpp files into .o files for the debug version
%.o_debug: %.cpp
		$(CXX) $(DEBUG_CXXFLAGS) -c $< -o $@

# Rule to create the test executable and run it
test: tests/test.sh
		chmod +x tests/test.sh
		./tests/test.sh

# Clean up
clean:
		rm -rf src/*.o src/*.o_debug runme runme_debug test gmon.out analysis.txt result.txt

.PHONY: all clean test debug
