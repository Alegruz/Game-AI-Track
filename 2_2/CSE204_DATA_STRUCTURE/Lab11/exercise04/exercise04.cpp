/*
 a.
 pq.Enqueue(28)
             56
        28---|---42
    26--|--27 3--|--19
 25-|-24 5-|-15

 pq.Enqueue(2)
               56
        28-----|-----42
    26--|--27     3--|--19
 25-|-24 5-|-15 2-|

 pq.Enqueue(40)
               56
        28-----|-----42
    26--|--27     40--|--19
 25-|-24 5-|-15 2-|-3

 pq.Dequeue(x)
               42
        28-----|-----40
    26--|--27     3--|--19
 25-|-24 5-|-15 2-|

 pq.Dequeue(y)
               40
        28-----|-----19
    26--|--27     3--|--2
 25-|-24 5-|-15

 pq.Dequeue(z)
               28
        27-----|-----19
    26--|--15     3--|--2
 25-|-24 5-|

 b. x = 56, y = 40, z = 40
 */
#include <cassert>
#include <iostream>
#include "PQType.h"

int main()
{
	PQType<int> pqueue(50);

	pqueue.Enqueue(56);
	pqueue.Enqueue(27);
	pqueue.Enqueue(42);
	pqueue.Enqueue(26);
	pqueue.Enqueue(15);
	pqueue.Enqueue(3);
	pqueue.Enqueue(19);
	pqueue.Enqueue(25);
	pqueue.Enqueue(24);
	pqueue.Enqueue(5);

	// a
	std::cout << "TEST A: ";
	pqueue.Enqueue(28);
	pqueue.Enqueue(2);
	pqueue.Enqueue(40);
	std::cerr << "SUCCESS" << std::endl;

	// b
	std::cout << "TEST B: ";
	int x = 0;
	int y = 0;
	int z = 0;
	pqueue.Dequeue(x);
	assert(x == 56);
	pqueue.Dequeue(y);
	assert(y == 42);
	pqueue.Dequeue(z);
	assert(z == 40);
	std::cout << "SUCCESS" << std::endl;

	return 0;
}