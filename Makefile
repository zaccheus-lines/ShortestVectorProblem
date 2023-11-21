all: file.c main.c
		gcc -o file file.c main.c

clean:
		rm -rf file
		rm -rf test

test:
		gcc -o test file.c tests/test.c
