all: exercise01 exercise02 exercise03 exercise04 exercise05

exercise01: exercise01.o StackType.o
	g++ -std=c++14 -Wall -o exercise01 exercise01.o StackType.o

exercise02: exercise02.o
	g++ -std=c++14 -Wall -o exercise02 exercise02.o

exercise03: exercise03.o
	g++ -std=c++14 -Wall -o exercise03 exercise03.o

exercise04: exercise04.o StackType.o
	g++ -std=c++14 -Wall -o exercise04 exercise04.o StackType.o

exercise05: exercise05.o StackType.o
	g++ -std=c++14 -Wall -o exercise05 exercise05.o StackType.o

exercise01.o: exercise01.cpp StackType.h
	g++ -std=c++14 -Wall -c exercise01.cpp

exercise02.o: exercise02.cpp QueType.h
	g++ -std=c++14 -Wall -c exercise02.cpp

exercise03.o: exercise03.cpp SortedType.h UnsortedType.h
	g++ -std=c++14 -Wall -c exercise03.cpp

exercise04.o: exercise04.cpp UnsortedType.h
	g++ -std=c++14 -Wall -c exercise04.cpp

exercise05.o: exercise05.cpp StackType.h
	g++ -std=c++14 -Wall -c exercise05.cpp

StackType.o: StackType.cpp StackType.h
	g++ -std=c++14 -Wall -c StackType.cpp