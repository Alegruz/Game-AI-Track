main: test.o SquareMatrix.o
	g++ -std=c++14 -Wall -o main test.o SquareMatrix.o

test.o: test.cpp SquareMatrix.h
	g++ -std=c++14 -Wall -c test.cpp

SquareMatrix.o: SquareMatrix.cpp SquareMatrix.h
	g++ -std=c++14 -Wall -c SquareMatrix.cpp