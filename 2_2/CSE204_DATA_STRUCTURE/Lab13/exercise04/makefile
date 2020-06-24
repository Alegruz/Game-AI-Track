PROG = exercise04
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = exercise04.o Student.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

exercise04.o : exercise04.cpp Student.h HashTable.h
	$(CC) $(CPPFLAGS) -c exercise04.cpp

Student.o : Student.cpp Student.h
	$(CC) $(CPPFLAGS) -c Student.cpp

clean :
	rm -f core $(PROG) $(OBJS)