#include "QueType.h"

#include <cassert>
#include <iostream>

using namespace lab5_6;

int main()
{
	srand( time( NULL ));
	
	QueType qt(10);
	ItemType item;

	std::cout << "ENQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		item = static_cast<ItemType>( rand() % 10 );
		std::cout << static_cast<int>( item ) << std::endl;
		qt.Enqueue( item );
	}

	std::cout << "\nMINIMUM DEQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		qt.MinDequeue(item);
		std::cout << static_cast<int>( item ) << std::endl;
	}

	std::cout << "ENQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		item = static_cast<ItemType>( 9 - count );
		std::cout << static_cast<int>( item ) << std::endl;
		qt.Enqueue( item );
	}

	std::cout << "\nMINIMUM DEQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		qt.MinDequeue(item);
		std::cout << static_cast<int>( item ) << std::endl;
	}

	return 0;
}