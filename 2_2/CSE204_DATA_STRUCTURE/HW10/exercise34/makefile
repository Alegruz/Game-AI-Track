exercise34: exercise34.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise34 exercise34.o TreeType.o QueType.o

exercise34.o: exercise34.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise34.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp