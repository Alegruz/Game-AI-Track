#pragma once

#include <cassert>

template <typename T>
class UnsortedList
{
public:
	UnsortedList();
	UnsortedList(unsigned int capacity);
	UnsortedList(const UnsortedList& other);
	virtual ~UnsortedList();

	UnsortedList& operator=(const UnsortedList& other);
	T& operator[](unsigned int index) const;

	bool Insert(const T& itemToInsert);
	bool Insert(unsigned int index, const T& itemToInsert);
	bool Delete(unsigned int index);
	int Search(const T& itemToSearch) const;
	void Merge(const UnsortedList& other);
	void RemoveDuplicates();
	unsigned int Size() const;
	unsigned int Capacity() const;

private:
	unsigned int mCapacity;
	unsigned int mSize;
	T* mItems;
};

template <typename T>
UnsortedList<T>::UnsortedList()
	: mCapacity(8), mSize(0), mItems(new T[mCapacity])
{
}

template <typename T>
UnsortedList<T>::UnsortedList(unsigned int capacity)
	: mCapacity(capacity), mSize(0), mItems(new T[mCapacity])
{
}

template <typename T>
UnsortedList<T>::UnsortedList(const UnsortedList& other)
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
UnsortedList<T>::~UnsortedList()
{
	delete[] mItems;
}

template <typename T>
UnsortedList<T>& UnsortedList<T>::operator=(const UnsortedList& other)
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
T& UnsortedList<T>::operator[](unsigned int index) const
{
	assert( index < mSize );

	return mItems[index];
}

template <typename T>
bool UnsortedList<T>::Insert(const T& itemToInsert)
{
	if (mCapacity <= mSize)
	{
		return false;
	}

	mItems[mSize] = itemToInsert;
	++mSize;

	return true;
}

template <typename T>
bool UnsortedList<T>::Insert(unsigned int index, const T& itemToInsert)
{
	if (mCapacity <= mSize)
	{
		return false;
	}

	for (unsigned int item = mSize; item > index; --item)
	{
		mItems[item] = mItems[item - 1];
	}

	mItems[index] = itemToInsert;
	++mSize;

	return true;
}

template <typename T>
bool UnsortedList<T>::Delete(unsigned int index)
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
int UnsortedList<T>::Search(const T& itemToSearch) const
{
	for (unsigned int item = 0; item < mSize; ++item)
	{
		if (mItems[item] == itemToSearch)
		{
			T temp = mItems[0];
			mItems[0] = mItems[item];
			mItems[item] = temp;
			return item;
		}
	}

	return -1;
}

template <typename T>
void UnsortedList<T>::Merge(const UnsortedList& other)
{
	if (mCapacity < mSize + other.mSize)
	{
		T tempList[mSize];

		for (unsigned int item = 0; item < mSize; ++item)
		{
			tempList[item] = mItems[item];
		}

		delete[] mItems;

		mCapacity += other.mCapacity;
		mItems = new T[mCapacity];

		for (unsigned int item = 0; item < mSize; ++item)
		{
			mItems[item] = tempList[item];
		}
	}

	for (unsigned int item = mSize; item < mSize + other.mSize; ++item)
	{
		mItems[item] = other.mItems[item - mSize];
	}

	mSize += other.mSize;
}

template <typename T>
void UnsortedList<T>::RemoveDuplicates()
{
	for (unsigned int item = 0; item < mSize; ++item)
	{
		for (unsigned int itemToCompare = item + 1; itemToCompare < mSize; ++itemToCompare)
		{
			if (mItems[item] == mItems[itemToCompare])
			{
				--mSize;
				for (unsigned int itemToRemove = itemToCompare; itemToRemove < mSize; ++itemToRemove)
				{
					mItems[itemToRemove] = mItems[itemToRemove + 1];
				}
			}
		}
	}
}

template <typename T>
unsigned int UnsortedList<T>::Size() const
{
	return mSize;
}

template <typename T>
unsigned int UnsortedList<T>::Capacity() const
{
	return mCapacity;
}