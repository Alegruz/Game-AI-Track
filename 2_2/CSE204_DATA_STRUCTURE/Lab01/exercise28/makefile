main: exercise28.o SquareMatrix.o
	g++ -std=c++14 -Wall -o main exercise28.o SquareMatrix.o

exercise28.o: exercise28.cpp SquareMatrix.h
	g++ -std=c++14 -Wall -c exercise28.cpp

SquareMatrix.o: SquareMatrix.cpp SquareMatrix.h
	g++ -std=c++14 -Wall -c SquareMatrix.cpp