#pragma once

#include <iostream>

#include "Swap.h"

template <class ItemType>
int GetHeight(ItemType values[], int start, int numValues)
{
	if (start > numValues || (start * 2 + 1 > numValues && start * 2 + 2 > numValues))
	{
		return 0;
	}
	int l_height = GetHeight(values, start * 2 + 1, numValues);
	int r_height = GetHeight(values, start * 2 + 2, numValues);

	return (l_height > r_height) ? l_height + 1 : r_height + 1;
}

template <class ItemType>
int GetHeightSum(ItemType values[], int numValues)
{
	int index;
	int sum = 0;
	for (index = 0; index < numValues && (index * 2 + 1 < numValues && index * 2 + 2 < numValues); ++index)
	{
		sum += GetHeight(values, index, numValues - 1);
	}

	std::cout << "sum of heights = " << sum << std::endl;

	return sum;
}

template <class ItemType>
void Print(ItemType values[], int numValues)
{
	for (int i = 0; i < numValues; ++i)
	{
		std::cout << values[i] << " ";
	}
	std::cout << "\b" << std::endl;
}

template <class ItemType>
void ReheapDown(ItemType elements[], int root, int bottom)
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
			if (elements[leftChild] <= elements[rightChild])
			{
				maxChild = rightChild;
			}
			else
			{
				maxChild = leftChild;
			}
		}
		if (elements[root] < elements[maxChild])
		{
			Swap(elements[root], elements[maxChild]);
			ReheapDown(elements, maxChild, bottom);
		}
	}
}

template <class ItemType>
void HeapSort(ItemType values[], int numValues)
// Pre:  Struct HeapType is available.
// Post: The elements in the array values are sorted by key.
{
	int index;

	std::cout << "INITIAL INPUT: ";
	Print(values, numValues);
	// Convert the array of values into a heap.
	for (index = numValues/2 - 1; index >= 0; index--)
	{
		ReheapDown(values, index, numValues-1);
	}

	std::cout << "HEAPIFIED: ";
	Print(values, numValues);
	// Sort the array.
	for (index = numValues-1; index >=1; index--)
	{
		Swap(values[0], values[index]);
		ReheapDown(values, 0, index-1);
		std::cout << "REHEAPED: ";
		Print(values, numValues);
	}
}