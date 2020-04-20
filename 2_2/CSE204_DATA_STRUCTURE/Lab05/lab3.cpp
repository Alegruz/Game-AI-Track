#include "QueType.h"

#include <cassert>
#include <iostream>
#include <memory>

using namespace lab1_4;

bool Identical(QueType& queue1, QueType& queue2);

int main()
{
	QueType qt1(5);
	std::cout << "Empty Identical Queue: ";
	assert( Identical(qt1, qt1) );
	assert( qt1.Identical(qt1) );
	std::cout << "SUCCESS" << std::endl;
	
	QueType qt2(5);
	for (unsigned int number = 0; number < 5; ++number)
	{
		qt1.Enqueue(number);
		qt2.Enqueue(number);
	}
	std::cout << "Same Size Same Value Queue: ";
	assert( Identical(qt1, qt2) );
	assert( qt1.Identical(qt2) );
	std::cout << "SUCCESS" << std::endl;

	QueType qt3(5);
	for (unsigned int number = 0; number < 4; ++number)
	{
		qt3.Enqueue(number);
	}
	qt3.Enqueue(6);

	std::cout << "Same Size Different Value Queue: ";
	assert( !Identical(qt1, qt3) );
	assert( !qt1.Identical(qt3) );
	std::cout << "SUCCESS" << std::endl;

	QueType qt4;
	std::cout << "Empty Queue to Non-empty Queue: ";
	assert( !Identical(qt1, qt4) );
	assert( !qt1.Identical(qt4) );
	std::cout << "SUCCESS" << std::endl;

	QueType qt5;
	std::cout << "Same Empty Queue: ";
	assert( Identical(qt4, qt5) );
	assert( qt4.Identical(qt5) );
	std::cout << "SUCCESS" << std::endl;

	QueType qt6(5);
	qt6.Enqueue(4);
	qt6.Enqueue(0);
	qt6.Enqueue(1);
	qt6.Enqueue(2);
	qt6.Enqueue(3);

	std::cout << "Same Size Same Value Different Order: ";
	assert( Identical(qt1, qt6) );
	assert( qt1.Identical(qt6) );
	std::cout << "SUCCESS" << std::endl;

	QueType qt7(10);
	qt7.Enqueue(2);
	qt7.Enqueue(3);
	qt7.Enqueue(4);
	qt7.Enqueue(0);
	qt7.Enqueue(1);

	std::cout << "Differenct Size Same Value Different Order: ";
	assert( qt1.Identical(qt7) );
	assert( qt1.Identical(qt7) );
	std::cout << "SUCCESS" << std::endl;


	return 0;
}

bool Identical(QueType& queue1, QueType& queue2)
{
	if (&queue1 == &queue2)
	{
		return true;
	}

	if (queue1.IsEmpty() && queue2.IsEmpty())
	{
		return true;
	}

	QueType tempQueue1;
	QueType tempQueue2;
	size_t queueSize1 = 0;
	size_t queueSize2 = 0;
	ItemType item1;
	ItemType item2;

	while (!queue1.IsEmpty())
	{
		queue1.Dequeue(item1);
		tempQueue1.Enqueue(item1);
		++queueSize1;
	}

	while (!tempQueue1.IsEmpty())
	{
		tempQueue1.Dequeue(item1);
		queue1.Enqueue(item1);
	}

	while (!queue2.IsEmpty())
	{
		queue2.Dequeue(item1);
		tempQueue2.Enqueue(item1);
		++queueSize2;
	}

	while (!tempQueue2.IsEmpty())
	{
		tempQueue2.Dequeue(item1);
		queue2.Enqueue(item1);
	}

	std::unique_ptr<ItemType[]> itemArray1 = std::make_unique<ItemType[]>(queueSize1 + 1);
	std::unique_ptr<ItemType[]> itemArray2 = std::make_unique<ItemType[]>(queueSize2 + 1);

	for (size_t item = 0; item < queueSize1; ++item)
	{
		queue1.Dequeue(item1);
		itemArray1[item] = item1;
		queue1.Enqueue(item1);
	}

	for (size_t item = 0; item < queueSize2; ++item)
	{
		queue2.Dequeue(item2);
		itemArray2[item] = item2;
		queue2.Enqueue(item2);
	}

	for (unsigned int item = 0, otherItem = 0;
		otherItem < queueSize2;
		otherItem = (otherItem + 1) % (queueSize2 + 1))
	{
		if (itemArray1[item] == itemArray2[otherItem])
		{
			unsigned int searchIndex;
			unsigned int otherSearchIndex;
			for (searchIndex = (item == queueSize1 - 1) ? 0 : (item + 1) % (queueSize1 + 1),
				otherSearchIndex = (otherItem == queueSize2 - 1) ? 0 : (otherItem + 1) % (queueSize2 + 1);
				searchIndex != item && otherSearchIndex != otherItem && itemArray1[searchIndex] == itemArray2[otherSearchIndex];
				searchIndex = (searchIndex == queueSize1 - 1) ? 0 : (searchIndex + 1) % (queueSize1 + 1), 
				otherSearchIndex = (otherSearchIndex == queueSize2 - 1) ? 0 : (otherSearchIndex + 1) % (queueSize2 + 1))
			{
			}

			if (searchIndex == item && otherSearchIndex == otherItem)
			{
				return true;
			}
		}
	}

	return false;
}