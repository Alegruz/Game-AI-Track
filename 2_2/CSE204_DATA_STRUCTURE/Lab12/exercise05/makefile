PROG = exercise05
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise05.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise05.o : exercise05.cpp HeapSort.h
	$(CC) $(CPPFLAGS) -c exercise05.cpp

clean :
	rm -f core $(PROG) $(OBJS)