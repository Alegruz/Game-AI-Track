PROG = main
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = main.o Board.o Piece.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

main.o : main.cpp Board.h
	$(CC) $(CPPFLAGS) -c main.cpp

Game.o : Game.cpp Game.h Board.h Piece.h
	$(CC) $(CPPFLAGS) -c Game.cpp

Board.o : Board.cpp Board.h Piece.h
	$(CC) $(CPPFLAGS) -c Board.cpp

Piece.o : Piece.cpp Piece.h
	$(CC) $(CPPFLAGS) -c Piece.cpp

clean :
	rm -f core $(PROG) $(OBJS)