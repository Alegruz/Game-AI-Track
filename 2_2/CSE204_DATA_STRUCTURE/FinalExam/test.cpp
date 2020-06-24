#include <cassert>
#include <iostream>

#include "PQType.h"

int main()
{
	PQType pq(8);
	assert(pq.IsEmpty());
	assert(!pq.IsFull());

	for (size_t i = 0; i < 8; ++i)
	{
		pq.Enqueue(i);
		assert(!pq.IsEmpty());
	}
	
	assert(pq.IsFull());

	int itemToShow;
	for (size_t i = 0; i < 8; ++i)
	{
		pq.Dequeue(itemToShow);
		std::cout << "Dequeued " << itemToShow << std::endl;
	}

	assert(pq.IsEmpty());
	assert(!pq.IsFull());

	// for (size_t i = 0; i < 8; ++i)
	// {
	// 	pq.Enqueue(i);
	// 	assert(!pq.IsEmpty());
	// }
	
	// assert(pq.IsFull());

	// pq.MakeEmpty();

	// assert(pq.IsEmpty());
	// assert(!pq.IsFull());

	return 0;
}