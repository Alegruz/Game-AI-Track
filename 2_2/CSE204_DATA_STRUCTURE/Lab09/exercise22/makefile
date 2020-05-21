exercise22: exercise22.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise22 exercise22.o TreeType.o QueType.o

exercise22.o: exercise22.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise22.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp