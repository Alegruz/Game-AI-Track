exercise21: exercise21.o TreeType.o QueType.o
	g++ -std=c++14 -Wall -o exercise21 exercise21.o TreeType.o QueType.o

exercise21.o: exercise21.cpp TreeType.h
	g++ -std=c++14 -Wall -c exercise21.cpp

TreeType.o: TreeType.cpp TreeType.h QueType.h
	g++ -std=c++14 -Wall -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp