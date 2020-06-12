PROG = exercise03
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise03.o Student.o InsertionSort.o Swap.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise03.o : exercise03.cpp Student.h InsertionSort.h
	$(CC) $(CPPFLAGS) -c exercise03.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

InsertionSort.o : InsertionSort.cpp InsertionSort.h
	$(CC) $(CPPFLAGS) -c InsertionSort.cpp

Swap.o : Swap.cpp Student.h
	$(CC) $(CPPFLAGS) -c Swap.cpp

clean :
	rm -f core $(PROG) $(OBJS)