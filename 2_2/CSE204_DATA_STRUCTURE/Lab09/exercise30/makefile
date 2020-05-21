exercise30: exercise30.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise30 exercise30.o TreeType.o QueType.o

exercise30.o: exercise30.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise30.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp