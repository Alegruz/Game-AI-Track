PROG = exercise03
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise03.o Student.o QuickSortPointer.o Swap.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise03.o : exercise03.cpp Student.h QuickSortPointer.h
	$(CC) $(CPPFLAGS) -c exercise03.cpp

QuickSortPointer.o : QuickSortPointer.cpp QuickSortPointer.h Swap.h
	$(CC) $(CPPFLAGS) -c QuickSortPointer.cpp

Swap.o : Swap.cpp Swap.h Student.h
	$(CC) $(CPPFLAGS) -c Swap.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

clean :
	rm -f core $(PROG) $(OBJS)