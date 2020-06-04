exercise27: exercise27.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise27 exercise27.o TreeType.o QueType.o

exercise27.o: exercise27.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise27.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp