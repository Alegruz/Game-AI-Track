PROG = exercise06
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise06.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise06.o : exercise06.cpp HeapSort.h
	$(CC) $(CPPFLAGS) -c exercise06.cpp

clean :
	rm -f core $(PROG) $(OBJS)