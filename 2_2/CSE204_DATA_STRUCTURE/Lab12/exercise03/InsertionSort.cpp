#include <cstring>

#include "InsertionSort.h"

void InsertItem(Student values[], int startIndex, int endIndex)
{
	bool bFinished = false;
	int current = endIndex;
	bool bMoreToSearch = (current != startIndex);

	while (bMoreToSearch && !bFinished)
	{
		if (strcmp(values[current].getName(), values[current - 1].getName()) < 0)
		{
			Swap(values[current], values[current - 1]);
			--current;
			bMoreToSearch = (current != startIndex);
		}
		else
		{
			bFinished = true;
		}
	}
}

void InsertionSort(Student ary[], int numElems)
{
	for (int count = 0; count < numElems; ++count)
	{
		InsertItem(ary, 0, count);
	}
}