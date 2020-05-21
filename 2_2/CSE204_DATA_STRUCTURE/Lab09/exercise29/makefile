exercise29: exercise29.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise29 exercise29.o TreeType.o QueType.o

exercise29.o: exercise29.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise29.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp