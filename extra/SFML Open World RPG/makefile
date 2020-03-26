PROG = main
CC = g++
CPPFLAGS = -std=c++14 -Wall -O2
OBJS = main.o Game.o State.o GameState.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

Game.o : Game.h
	$(CC) $(CPPFLAGS) -c Game.cpp

GameState.o : states/GameState.h
	$(CC) $(CPPFLAGS) -c states/GameState.cpp

State.o : states/State.h
	$(CC) $(CPPFLAGS) -c states/State.cpp

clean :
	rm -f core $(PROG) $(OBJS)