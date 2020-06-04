#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Heap.h"

int main()
{
	srand(time(NULL));
	HeapType<int> ht;
	ht.elements = new int[10];
	int maxIndex = 0;
	int minIndex = 0;
	
	for (size_t i = 0; i < 10; ++i)
	{
		int number = rand() % 100 + 1;
		ht.elements[i] = number;
		std::cout << "[" << i << "]: " << number << std::endl;

		if (number < ht.elements[minIndex])
		{
			minIndex = i;
		}

		if (number > ht.elements[maxIndex])
		{
			maxIndex = i;
		}
	}

	ht.ReheapDown(maxIndex, minIndex);

	for (size_t i = 0; i < 10; ++i)
	{
		std::cout << "[" << i << "]: " << ht.elements[i] << std::endl;
	}


	return 0;
}