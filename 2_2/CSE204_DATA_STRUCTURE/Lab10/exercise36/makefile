exercise36: exercise36.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise36 exercise36.o TreeType.o QueType.o

exercise36.o: exercise36.cpp TreeType.h UnsortedType.h
	g++ -std=c++14 -Wall -c exercise36.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp