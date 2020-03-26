main: main.o sorted.o ItemType.o
	g++ -std=c++14 -Wall -o main main.o sorted.o ItemType.o

main.o: main.cpp ItemType.h sorted.h
	g++ -std=c++14 -Wall -c main.cpp

sorted.o: sorted.cpp sorted.h ItemType.h
	g++ -std=c++14 -Wall -c sorted.cpp

ItemType.o: ItemType.cpp ItemType.h
	g++ -std=c++14 -Wall -c ItemType.cpp