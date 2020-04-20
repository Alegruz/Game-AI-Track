#include "QueType.h"

#include <cstdlib>
#include <iostream>

using namespace lab1_4;

void ReplaceItem(QueType& queue, int oldItem, int newItem);

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

	ReplaceItem(qt, 4, 1000);
	qt.ReplaceItem(3, 3000);

	std::cout << "\nREPLACED" << std::endl;
	for (size_t count = 0; count < 10; ++count)
	{
		qt.Dequeue(item);
		std::cout << static_cast<int>( item ) << std::endl;
	}

	return 0;
}

void ReplaceItem(QueType& queue, int oldItem, int newItem)
{
	if (queue.IsEmpty())
	{
		return;
	}

	QueType tempQueue;
	ItemType itemToEnqueue;
	while (!queue.IsEmpty())
	{
		queue.Dequeue(itemToEnqueue);

		if ( itemToEnqueue == static_cast<ItemType>( oldItem ) )
		{
			itemToEnqueue = static_cast<ItemType>( newItem );
		}

		tempQueue.Enqueue(itemToEnqueue);
	}

	while (!tempQueue.IsEmpty())
	{
		tempQueue.Dequeue(itemToEnqueue);
		queue.Enqueue(itemToEnqueue);
	}
	
}