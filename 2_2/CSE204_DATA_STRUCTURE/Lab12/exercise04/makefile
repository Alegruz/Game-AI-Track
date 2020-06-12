PROG = exercise04
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise04.o Student.o HeapSort.o Swap.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise04.o : exercise04.cpp Student.h HeapSort.h
	$(CC) $(CPPFLAGS) -c exercise04.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

HeapSort.o : HeapSort.cpp HeapSort.h
	$(CC) $(CPPFLAGS) -c HeapSort.cpp

Swap.o : Swap.cpp Student.h
	$(CC) $(CPPFLAGS) -c Swap.cpp

clean :
	rm -f core $(PROG) $(OBJS)