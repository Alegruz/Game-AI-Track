main: Client.o SortedType.o HouseType.o IOhandler.o
	g++ -std=c++14 -Wall -o main Client.o SortedType.o HouseType.o IOhandler.o

Client.o: Client.cpp SortedType.h
	g++ -std=c++14 -Wall -c Client.cpp

SortedType.o: SortedType.cpp SortedType.h HouseType.h
	g++ -std=c++14 -Wall -c SortedType.cpp

HouseType.o: HouseType.cpp HouseType.h IOhandler.h
	g++ -std=c++14 -Wall -c HouseType.cpp

IOhandler.o: IOhandler.cpp IOhandler.h
	g++ -std=c++14 -Wall -c IOhandler.cpp