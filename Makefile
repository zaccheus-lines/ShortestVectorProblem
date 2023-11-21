all: src/svp_solver.cpp src/main.cpp
		gpp -o rumme src/svp_solver.cpp src/main.cpp

clean:
		rm -rf svp_solver
		rm -rf test

test:
		gpp -o test src/svp_solver.cpp tests/test.cpp
