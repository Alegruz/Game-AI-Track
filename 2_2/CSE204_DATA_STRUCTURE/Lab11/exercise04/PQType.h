#pragma once
// Definition of class PQType, which represents the Priority Queue ADT
class FullPQ
{
};
class EmptyPQ
{
};
#include "Heap.h"
template <class ItemType>
class PQType
{
public:
	PQType(int); // parameterized class constructor
	~PQType();	 // class destructor

	void MakeEmpty();
	// Function: Initializes the queue to an empty state.
	// Post: Queue is empty.

	bool IsEmpty() const;
	// Function: Determines whether the queue is empty.
	// Post: Function value = (queue is empty)

	bool IsFull() const;
	// Function: Determines whether the queue is full.
	// Post: Function value = (queue is full)

	void Enqueue(ItemType newItem);
	// Function: Adds newItem to the rear of the queue.
	// Post: if (the priority queue is full) exception FullPQ is thrown;
	//       else newItem is in the queue.

	void Dequeue(ItemType &item);
	// Function: Removes element with highest priority from the queue
	// and returns it in item.
	// Post: If (the priority queue is empty) exception EmptyPQ is thrown;
	//       else highest priority element has been removed from queue.
	//       item is a copy of removed element.
private:
	int mLength;
	HeapType<ItemType> mItems;
	int mMaxItems;
};

template <class ItemType>
PQType<ItemType>::PQType(int max)
{
	mMaxItems = max;
	mItems.elements = new ItemType[max];
	mLength = 0;
}

template <class ItemType>
void PQType<ItemType>::MakeEmpty()
{
	mLength = 0;
}

template <class ItemType>
PQType<ItemType>::~PQType()
{
	delete[] mItems.elements;
}
template <class ItemType>
void PQType<ItemType>::Dequeue(ItemType& item)
// Post: element with highest priority has been removed
//       from the queue; a copy is returned in item.
{
	if (mLength == 0)
		throw EmptyPQ();
	else
	{
		item = mItems.elements[0];
		mItems.elements[0] = mItems.elements[mLength - 1];
		mLength--;
		mItems.ReheapDown(0, mLength - 1);
	}
}

template <class ItemType>
void PQType<ItemType>::Enqueue(ItemType newItem)
// Post: newItem is in the queue.
{
	if (mLength == mMaxItems)
		throw FullPQ();
	else
	{
		mLength++;
		mItems.elements[mLength - 1] = newItem;
		mItems.ReheapUp(0, mLength - 1);
	}
}
template <class ItemType>
bool PQType<ItemType>::IsFull() const
// Post: Returns true if the queue is full; false, otherwise.
{
	return mLength == mMaxItems;
}

template <class ItemType>
bool PQType<ItemType>::IsEmpty() const
// Post: Returns true if the queue is empty; false, otherwise.
{
	return mLength == 0;
}
