all: svp_solver.c main.c
		gcc -o svp_solver svp_solver.c main.c

clean:
		rm -rf svp_solver
		rm -rf test

test:
		gcc -o test svp_solver.c tests/test.c
