main: Client.o DoubleStack.o
	g++ -std=c++14 -Wall -o main Client.o DoubleStack.o

Client.o: Client.cpp DoubleStack.h
	g++ -std=c++14 -Wall -c Client.cpp

DoubleStack.o: DoubleStack.cpp DoubleStack.h
	g++ -std=c++14 -Wall -c DoubleStack.cpp