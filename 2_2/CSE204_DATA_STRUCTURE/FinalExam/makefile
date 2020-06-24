PROG = test
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = test.o PQType.o LLHeapType.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

test.o : test.cpp PQType.h LLHeapType.h
	$(CC) $(CPPFLAGS) -c test.cpp

PQType.o : PQType.cpp PQType.h LLHeapType.h
	$(CC) $(CPPFLAGS) -c PQType.cpp

LLHeapType.o : LLHeapType.cpp LLHeapType.h
	$(CC) $(CPPFLAGS) -c LLHeapType.cpp

clean :
	rm -f core $(PROG) $(OBJS)