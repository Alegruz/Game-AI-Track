PROG = exercise02
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise02.o Student.o MergeSort.o Swap.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise02.o : exercise02.cpp Student.h MergeSort.h
	$(CC) $(CPPFLAGS) -c exercise02.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

MergeSort.o : MergeSort.cpp MergeSort.h
	$(CC) $(CPPFLAGS) -c MergeSort.cpp

Swap.o : Swap.cpp MergeSort.h
	$(CC) $(CPPFLAGS) -c Swap.cpp

clean :
	rm -f core $(PROG) $(OBJS)