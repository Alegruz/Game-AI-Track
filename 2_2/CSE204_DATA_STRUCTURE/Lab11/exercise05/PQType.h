#pragma once

class FullPQ
{
};
class EmptyPQ
{
};

#include "SortedType.h"	// Heap.h 대신 SortedType.h 추가

template <class ItemType>
class PQType
{
public:
	PQType();
	~PQType();

	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	void Enqueue(ItemType newItem);
	void Dequeue(ItemType &item);

private:
	int mLength;
	SortedType<ItemType>* mItems;	// Heap에서 SorteType으로 변경
};

template <class ItemType>
PQType<ItemType>::PQType()
	: mLength(0),
	mItems = new SortedType<ItemType>()
{
}

template <class ItemType>
void PQType<ItemType>::MakeEmpty()
{
	mLength = 0;
	mItems->MakeEmpty();
}

template <class ItemType>
PQType<ItemType>::~PQType()
{
	delete[] mItems;
}

template <class ItemType>
void PQType<ItemType>::Dequeue(ItemType& item)
// Post: element with highest priority has been removed
//       from the queue; a copy is returned in item.
{
	if (mLength == 0)
	{
		throw EmptyPQ();
	}
	else
	{
		mItems->ResetList();
		mItems->GetNextItem(item);

		if (bFoundItem)
		{
			mItems->DeleteItem(item);
		}
		--mLength;
		mItems->ResetList();
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
		++mLength;
		mItems->InsertItem(newItem);
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
