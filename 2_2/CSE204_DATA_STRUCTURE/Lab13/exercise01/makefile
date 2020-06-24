PROG = exercise01
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise01.o Student.o QuickSort.o Swap.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise01.o : exercise01.cpp Student.h QuickSort.h
	$(CC) $(CPPFLAGS) -c exercise01.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

QuickSort.o : QuickSort.cpp QuickSort.h
	$(CC) $(CPPFLAGS) -c QuickSort.cpp

Swap.o : Swap.cpp QuickSort.h
	$(CC) $(CPPFLAGS) -c Swap.cpp

clean :
	rm -f core $(PROG) $(OBJS)