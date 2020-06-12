#include <cstring>

#include "HeapSort.h"

void ReheapDown(Student elements[], int root, int bottom)
// Post: Heap property is restored.
{
	int maxChild;
	int rightChild;
	int leftChild;

	leftChild = root*2+1;
	rightChild = root*2+2;
	if (leftChild <= bottom)
	{
		if (leftChild == bottom)
		{
			maxChild = leftChild;
		}
		else
		{
			if (strcmp(elements[leftChild].getName(), elements[rightChild].getName()) <= 0)
			{
				maxChild = rightChild;
			}
			else
			{
				maxChild = leftChild;
			}
		}
		if (strcmp(elements[root].getName(), elements[maxChild].getName()) < 0)
		{
			Swap(elements[root], elements[maxChild]);
			ReheapDown(elements, maxChild, bottom);
		}
	}
}

void HeapSort(Student values[], int numValues)
// Pre:  Struct HeapType is available.
// Post: The elements in the array values are sorted by key.
{
  int index;

	// Convert the array of values into a heap.
	for (index = numValues/2 - 1; index >= 0; index--)
	{
		ReheapDown(values, index, numValues-1);
	}

	// Sort the array.
	for (index = numValues-1; index >=1; index--)
	{
		Swap(values[0], values[index]);
		ReheapDown(values, 0, index-1);
	}
}
