exercise35: exercise35.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise35 exercise35.o TreeType.o QueType.o

exercise35.o: exercise35.cpp TreeType.h SortedType.h
	g++ -std=c++14 -Wall -c exercise35.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp