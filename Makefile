# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

# Default target
all: runme

# Rule to create the runme executable
runme: src/main.o
		$(CXX) $(CXXFLAGS) -o runme src/main.o

# Rule to compile .cpp files into .o files
%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the test executable and run it
test: tests/test.o
		$(CXX) $(CXXFLAGS) -o test tests/test.o
		./test

# Clean up
clean:
		rm -rf src/*.o tests/*.o runme test

.PHONY: all clean test
