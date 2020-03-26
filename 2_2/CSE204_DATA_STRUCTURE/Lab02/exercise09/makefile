main: main.o unsorted.o ItemType.o
	g++ -std=c++14 -Wall -o main main.o unsorted.o ItemType.o

main.o: main.cpp ItemType.h unsorted.h
	g++ -std=c++14 -Wall -c main.cpp

unsorted.o: unsorted.cpp unsorted.h ItemType.h
	g++ -std=c++14 -Wall -c unsorted.cpp

ItemType.o: ItemType.cpp ItemType.h
	g++ -std=c++14 -Wall -c ItemType.cpp