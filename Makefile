# Default target
all: runme

# Rule to create the runme executable
runme: src/svp_solver.o src/main.o
		g++ -Wall -Werror -o runme src/svp_solver.o src/main.o

# Rule to compile .cpp files into .o files
%.o: %.cpp
		g++ -Wall -Werror -c $< -o $@

# Rule to create the test executable and run it
test: src/svp_solver.o tests/test.o
		g++ -Wall -Werror -o test src/svp_solver.o tests/test.o
		./test

# Clean up
clean:
		rm -rf src/*.o tests/*.o runme test

.PHONY: all clean test
