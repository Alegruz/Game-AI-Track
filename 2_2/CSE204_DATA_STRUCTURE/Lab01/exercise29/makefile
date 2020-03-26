main: main.o StrType.o
	g++ -std=c++14 -Wall -o main main.o StrType.o

main.o: main.cpp StrType.h
	g++ -std=c++14 -Wall -c main.cpp

StrType.o: StrType.cpp StrType.h
	g++ -std=c++14 -Wall -c StrType.cpp