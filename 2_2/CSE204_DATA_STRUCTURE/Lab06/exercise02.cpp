#include "QueType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace exercise02;

template <class ItemType>
void ReplaceItem(QueType<ItemType>& queue, const ItemType& oldItem, const ItemType& newItem);

int main()
{
	srand ( time(NULL) );

	QueType<int> q1;
	size_t queueSize1 = rand() % 10;
	int item;
	for (size_t index = 0; index < queueSize1; ++index)
	{
		item = rand() % 10;
		q1.Enqueue(item);
	}
	std::cout << q1 << std::endl;
	ReplaceItem(q1, 3, 3000);
	std::cout << q1 << std::endl;
	q1.ReplaceItem(4, 4000);
	std::cout << q1 << std::endl;

	return 0;
}

template <class ItemType>
void ReplaceItem(QueType<ItemType>& queue, const ItemType& oldItem, const ItemType& newItem)
{
	if (queue.IsEmpty())
	{
		return;
	}

	QueType<ItemType> tempQueue;
	ItemType item;
	while (!queue.IsEmpty())
	{
		queue.Dequeue(item);
		if (item == oldItem)
		{
			item = newItem;
		}
		tempQueue.Enqueue(item);
	}

	while (!tempQueue.IsEmpty())
	{
		tempQueue.Dequeue(item);
		queue.Enqueue(item);
	}
}