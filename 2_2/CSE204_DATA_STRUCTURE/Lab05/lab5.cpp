#include "QueType.h"

#include <cassert>
#include <iostream>

using namespace lab5_6;

int main()
{
	srand( time( NULL ));

	QueType qt(10);
	ItemType item;

	assert( qt.IsEmpty() );

	std::cout << "ENQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		item = static_cast<ItemType>( rand() );
		std::cout << static_cast<int>( item ) << std::endl;
		qt.Enqueue( item );
	}

	assert( qt.IsFull() );

	std::cout << "\nDEQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		qt.Dequeue(item);
		std::cout << static_cast<int>( item ) << std::endl;
	}

	assert( qt.IsEmpty() );

	for (size_t count = 0; count < 10; ++count)
	{
		item = static_cast<ItemType>( rand() );
		qt.Enqueue( item );
	}
	qt.MakeEmpty();

	assert( qt.IsEmpty() );

	return 0;
}