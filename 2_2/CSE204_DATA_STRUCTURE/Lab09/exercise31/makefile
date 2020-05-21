exercise31: exercise31.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise31 exercise31.o TreeType.o QueType.o

exercise31.o: exercise31.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise31.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp