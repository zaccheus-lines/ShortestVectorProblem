# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -pg -g

# Source files
SOURCES = src/main.cpp src/vector.cpp src/lattice.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: runme

# Rule to create the runme executable
runme: $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o runme $(OBJECTS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the test executable and run it
test: tests/test.sh
		chmod +x tests/test.sh
		./tests/test.sh

# Clean up
clean:
		rm -rf src/*.o tests/*.o runme test gmon.out analysis.txt result.txt

.PHONY: all clean test
