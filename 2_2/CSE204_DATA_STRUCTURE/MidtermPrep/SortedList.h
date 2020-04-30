#pragma once

#include <cassert>

template <typename T>
class SortedList
{
public:
	SortedList();
	SortedList(unsigned int capacity);
	SortedList(const SortedList& other);
	virtual ~SortedList();

	SortedList& operator=(const SortedList& other);
	T& operator[](unsigned int index) const;

	bool Insert(const T& itemToInsert);
	bool Delete(unsigned int index);
	int Search(const T& item) const;
	void Merge(const SortedList& other);
	void RemoveDuplicates();
	unsigned int Size() const;
	unsigned int Capacity() const;

private:
	unsigned int mCapacity;
	unsigned int mSize;
	T* mItems;
};

template <typename T>
SortedList<T>::SortedList()
	: mCapacity(8), mSize(0), mItems(new T[mCapacity])
{
}

template <typename T>
SortedList<T>::SortedList(unsigned int capacity)
	: mCapacity(capacity), mSize(0), mItems(new T[mCapacity])
{
}

template <typename T>
SortedList<T>::SortedList(const SortedList& other)
{
	if (mItems != other.mItems)
	{
		mCapacity = other.mCapacity;
		mSize = other.mSize;
		mItems = new T[mCapacity];

		for (unsigned int item = 0; item < other.mSize; ++item)
		{
			mItems[item] = other.mItems[item];
		}
	}
}

template <typename T>
SortedList<T>::~SortedList()
{
	delete[] mItems;
}

template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{
	if (mItems != other.mItems)
	{
		if (mCapacity != other.mCapacity)
		{
			delete[] mItems;
			mCapacity = other.mCapacity;
			mItems = new T[mCapacity];
		}

		mSize = other.mSize;

		for (unsigned int item = 0; item < other.mSize; ++item)
		{
			mItems[item] = other.mItems[item];
		}
	}

	return *this;
}

template <typename T>
T& SortedList<T>::operator[](unsigned int index) const
{
	assert( index < mSize );

	return mItems[index];
}

template <typename T>
bool SortedList<T>::Insert(const T& itemToInsert)
{
	if (mCapacity <= mSize)
	{
		return false;
	}

	unsigned int head = 0;
	unsigned int tail = mSize;
	unsigned int middle;

	while (head <= tail)
	{
		middle = (head + tail) / 2;
		if (mItems[middle] < itemToInsert)
		{
			head = middle + 1;
		}
		else if (mItems[middle] > itemToInsert)
		{
			tail = middle - 1;
		}
		else
		{
			for (unsigned int item = mSize; item > middle + 1; --item)
			{
				mItems[mSize] = mItems[mSize - 1];
			}
			mItems[middle + 1] = itemToInsert;
			return true;
		}
	}

	if (mItems[middle] < itemToInsert)
	{
		for (unsigned int item = mSize; item > head; --item)
		{
			mItems[mSize] = mItems[mSize - 1];
		}
		mItems[head] = itemToInsert;	
	}
	else if (mItems[middle] > itemToInsert)
	{
		for (unsigned int item = mSize; item > tail + 1; --item)
		{
			mItems[mSize] = mItems[mSize - 1];
		}
		mItems[tail + 1] = itemToInsert;	
	}

	return true;
}

template <typename T>
bool SortedList<T>::Delete(unsigned int index)
{
	if (index >= mSize)
	{
		return false;
	}

	--mSize;
	for (unsigned int item = index; item < mSize; ++item)
	{
		mItems[item] = mItems[item + 1];
	}

	return true;
}

template <typename T>
int SortedList<T>::Search(const T& item) const
{
	unsigned int head = 0;
	unsigned int tail = mSize;
	unsigned int middle;

	while (head <= tail)
	{
		middle = (head + tail) / 2;
		if (mItems[middle] < item)
		{
			head = middle + 1;
		}
		else if (mItems[middle] > item)
		{
			tail = middle - 1;
		}
		else
		{
			return middle;
		}
	}

	return -1;
}

template <typename T>
void SortedList<T>::Merge(const SortedList& other)
{
	mCapacity += other.mCapacity;
	T* mergedList = new T[mCapacity];
	for (unsigned int myItem = 0, otherItem = 0, mergeIndex = 0; myItem < mSize && otherItem < other.mSize && mergeIndex < mCapacity; ++mergeIndex)
	{
		if (mItems[myItem] > other.mItems[otherItem])
		{
			mergedList[mergeIndex] = other.mItems[otherItem];
			++otherItem;
		}
		else
		{
			mergedList[mergeIndex] = mItems[myItem];
			++myItem;	
		}
	}

	delete[] mItems;
	mItems = mergedList;
	mergedList = nullptr;

	mSize += other.mSize;
}

template <typename T>
void SortedList<T>::RemoveDuplicates()
{
	for (unsigned int item = 0; item < mSize - 1; ++item)
	{
		if (mItems[item] == mItems[item + 1])
		{
			for (unsigned int itemToShift = item + 1; itemToShift < mSize - 1; ++itemToShift)
			{
				mItems[itemToShift] = mItems[itemToShift + 1];
			}
			--mSize;
		}
	}
}

template <typename T>
unsigned int SortedList<T>::Size() const
{
	return mSize;
}

template <typename T>
unsigned int SortedList<T>::Capacity() const
{
	return mCapacity;
}