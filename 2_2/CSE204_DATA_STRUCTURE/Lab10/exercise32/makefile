exercise32: exercise32.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise32 exercise32.o TreeType.o QueType.o

exercise32.o: exercise32.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise32.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp