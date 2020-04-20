#include "QueType.h"

#include <cstdlib>
#include <iostream>

using namespace lab1_4;

int main()
{
	srand( time( NULL ));
	
	QueType qt(10);
	ItemType item;

	std::cout << "ENQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		item = static_cast<ItemType>( rand() );
		std::cout << static_cast<int>( item ) << std::endl;
		qt.Enqueue( item );
	}

	std::cout << "\nDEQUEUEING" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		qt.Dequeue(item);
		std::cout << static_cast<int>( item ) << std::endl;
	}

	return 0;
}