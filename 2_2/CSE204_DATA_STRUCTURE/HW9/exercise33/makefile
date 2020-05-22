exercise33: exercise33.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise33 exercise33.o TreeType.o QueType.o

exercise33.o: exercise33.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise33.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp