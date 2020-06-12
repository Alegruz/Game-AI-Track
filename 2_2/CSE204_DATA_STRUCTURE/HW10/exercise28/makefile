exercise28: exercise28.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise28 exercise28.o TreeType.o QueType.o

exercise28.o: exercise28.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise28.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp