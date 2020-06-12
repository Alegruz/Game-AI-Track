PROG = exercise02
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise02.o Student.o BubbleSort.o Swap.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise02.o : exercise02.cpp Student.h BubbleSort.h
	$(CC) $(CPPFLAGS) -c exercise02.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

BubbleSort.o : BubbleSort.cpp BubbleSort.h
	$(CC) $(CPPFLAGS) -c BubbleSort.cpp

Swap.o : Swap.cpp Student.h
	$(CC) $(CPPFLAGS) -c Swap.cpp

clean :
	rm -f core $(PROG) $(OBJS)