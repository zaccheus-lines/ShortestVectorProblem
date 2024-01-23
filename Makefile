# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -O3

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

# Rule to compile .cpp files into .o files
%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@


# Rule to run Python tests
python_test:
		python3 tests/tests.py

# Rule to create the test executable and run it
test: runme python_test

# Clean up
clean:
		rm -rf src/*.o runme test result.txt

.PHONY: all clean test debug python_test
