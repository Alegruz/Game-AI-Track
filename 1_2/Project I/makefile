main: test.o MemoryPool.o
	g++ -std=c++14 -Wall -o main test.o MemoryPool.o

test.o: test.cpp MemoryPool.h
	g++ -std=c++14 -Wall -c test.cpp

MemoryPool.o: MemoryPool.cpp MemoryPool.h
	g++ -std=c++14 -Wall -c MemoryPool.cpp