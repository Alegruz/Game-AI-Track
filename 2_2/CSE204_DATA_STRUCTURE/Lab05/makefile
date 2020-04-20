all: lab1 lab2 lab3 lab4 lab5 lab6

lab1: lab1.o QueType.o
	g++ -std=c++14 -Wall -o lab1 lab1.o QueType.o

lab2: lab2.o QueType.o
	g++ -std=c++14 -Wall -o lab2 lab2.o QueType.o

lab3: lab3.o QueType.o
	g++ -std=c++14 -Wall -o lab3 lab3.o QueType.o

lab4: lab4.o QueType.o
	g++ -std=c++14 -Wall -o lab4 lab4.o QueType.o

lab5: lab5.o QueType.o
	g++ -std=c++14 -Wall -o lab5 lab5.o QueType.o

lab6: lab6.o QueType.o
	g++ -std=c++14 -Wall -o lab6 lab6.o QueType.o

lab1.o: lab1.cpp QueType.h
	g++ -std=c++14 -Wall -c lab1.cpp

lab2.o: lab2.cpp QueType.h
	g++ -std=c++14 -Wall -c lab2.cpp

lab3.o: lab3.cpp QueType.h
	g++ -std=c++14 -Wall -c lab3.cpp

lab4.o: lab4.cpp QueType.h
	g++ -std=c++14 -Wall -c lab4.cpp

lab5.o: lab5.cpp QueType.h
	g++ -std=c++14 -Wall -c lab5.cpp

lab6.o: lab6.cpp QueType.h
	g++ -std=c++14 -Wall -c lab6.cpp

QueType.o: QueType.cpp QueType.h
	g++ -std=c++14 -Wall -c QueType.cpp