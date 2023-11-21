all: src/svp_solver.cpp src/main.cpp
		g++ -o runme src/svp_solver.cpp src/main.cpp

clean:
		rm -rf runme
		rm -rf test

test:
		g++ -o test src/svp_solver.cpp tests/test.cpp
