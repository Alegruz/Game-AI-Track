#include "QueType.h"

#include <cassert>
#include <iostream>

using namespace lab1_4;

unsigned int Length(QueType& queue);

int main()
{
	QueType qt(10);
	std::cerr << "Empty Queue: ";
	assert( Length(qt) == 0);
	assert( qt.Length() == 0 );
	assert( qt.IsEmpty() );
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "Single Enqueue: ";
	qt.Enqueue(100);
	assert( Length(qt) == 1 );
	assert( qt.Length() == 1 );
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "Multiple Enqueue: ";
	for (unsigned int number = 0; number < 5; ++number)
	{
		qt.Enqueue(static_cast<ItemType>( number ));
	}
	assert( Length(qt) == 6 );
	assert( qt.Length() == 6 );
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "Full Enqueue: ";
	for (unsigned int number = 0; number < 4; ++number)
	{
		qt.Enqueue( static_cast<ItemType>(number * number) );
	}
	assert( Length(qt) == 10 );
	assert( qt.Length() == 10 );
	assert( qt.IsFull() );
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "Single Dequeue: ";
	ItemType item;
	qt.Dequeue( item );
	assert( Length(qt) == 9 );
	assert( qt.Length() == 9 );
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "Multiple Dequeue: ";
	for (unsigned int number = 0; number < 4; ++number)
	{
		qt.Dequeue( item );
	}
	assert( Length(qt) == 5 );
	assert( qt.Length() == 5 );
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "Full Dequeue: ";
	for (unsigned int number = 0; number < 5; ++number)
	{
		qt.Dequeue( item );
	}
	assert( Length(qt) == 0 );
	assert( qt.Length() == 0 );
	assert( qt.IsEmpty() );
	std::cerr << "SUCCESS" << std::endl;

	return 0;
}

unsigned int Length(QueType& queue)
{
	QueType tempQueue;
	unsigned int queueSize = 0;
	ItemType item;

	while (!queue.IsEmpty())
	{
		queue.Dequeue(item);
		tempQueue.Enqueue(item);
		++queueSize;
	}

	while (!tempQueue.IsEmpty())
	{
		tempQueue.Dequeue(item);
		queue.Enqueue(item);
	}

	return queueSize;
}