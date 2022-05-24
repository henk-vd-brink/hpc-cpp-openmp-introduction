all: example1 example2

example1:
	g++ src/example1.cpp -o bin/example1.out -fopenmp

example2:
	g++ src/example2.cpp -o bin/example2.out -fopenmp