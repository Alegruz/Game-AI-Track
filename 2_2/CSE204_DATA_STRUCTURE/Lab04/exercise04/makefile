main: Client.o StackType.o
	g++ -std=c++14 -Wall -o main Client.o StackType.o

Client.o: Client.cpp StackType.h
	g++ -std=c++14 -Wall -c Client.cpp

StackType.o: StackType.cpp StackType.h ItemType.h
	g++ -std=c++14 -Wall -c StackType.cpp