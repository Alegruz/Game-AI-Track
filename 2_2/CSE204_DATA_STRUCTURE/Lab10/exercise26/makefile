exercise26: exercise26.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise26 exercise26.o TreeType.o QueType.o

exercise26.o: exercise26.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise26.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp