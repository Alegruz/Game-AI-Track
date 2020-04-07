#pragma once
#include <iostream>

int BinarySearch(int* sortedList, unsigned int size, int item)
{
	if (sortedList == nullptr)
	{
		return -1;
	}

	unsigned int head = 0;
	unsigned int tail = size - 1;
	unsigned int middle;

	while(head <= tail)
	{
		middle = (head + tail ) / 2;
		if (sortedList[middle] > item)
		{
			if (middle == 0)
			{
				break;
			}
			tail = middle - 1;
		}	
		else if (sortedList[middle] < item)
		{
			head = middle + 1;
		}
		else
		{
			return middle;
		}
	}

	return -1;
}
	