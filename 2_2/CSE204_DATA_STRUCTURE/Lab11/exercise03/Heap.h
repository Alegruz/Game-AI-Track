template <class ItemType>
void swap(ItemType &one, ItemType &two);

#pragma once

template <class ItemType>
// Assumes ItemType is either a built-in simple type or a class
// with overloaded relational operators.
struct HeapType
{
	void ReheapDown(int root, int bottom);
	void ReheapUp(int root, int bottom);
	ItemType* elements; // Array to be allocated dynamically
	int numElements;
};

template <class ItemType>
void Swap(ItemType& one, ItemType& two)
{
	ItemType temp;
	temp = one;
	one = two;
	two = temp;
}

template <class ItemType>
void HeapType<ItemType>::ReheapUp(int root, int bottom)
// Post: Heap property is restored.
{
	int parent = 0;
	bool bIsReheaped = false;
	while (bottom > root && !bIsReheaped)
	{
		parent = (bottom - 1) / 2;
		if (elements[parent] < elements[bottom])
		{
			Swap(elements[parent], elements[bottom]);
			bottom = parent;
		}
		else
		{
			bIsReheaped = true;
		}
	}
}

template <class ItemType>
void HeapType<ItemType>::ReheapDown(int root, int bottom)
// Post: Heap property is restored.
{
	bool bIsReheaped = false;
	int maxChild = 0;
	int rightChild = 0;
	int leftChild = 0;
	while (root * 2 + 1 <= bottom && !bIsReheaped)
	{
		rightChild = root * 2 + 2;
		leftChild = root * 2 + 1;
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
			root = maxChild;
		}
	}
}

/*
 c. The space complexity might be constant O(1) for nonrecursive version, but the time complexity still remains as O(log2(n)) because the algorithm itself remains the same.
	We still have to traverse through the height of the heap, which is log2(n).
 */