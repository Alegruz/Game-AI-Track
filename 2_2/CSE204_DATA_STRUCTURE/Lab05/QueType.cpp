#include "QueType.h"

#include <iostream>

namespace lab1_4
{
	QueType::QueType(unsigned int max)
		: mMaxQue(max + 1)
		, mFront(mMaxQue - 1)
		, mRear(mMaxQue - 1)
		, mItems(new ItemType[mMaxQue])
	{
	}

	QueType::QueType()
		: mMaxQue(501)
		, mFront(mMaxQue - 1)
		, mRear(mMaxQue - 1)
		, mItems(new ItemType[mMaxQue])
	{
	}

	QueType::~QueType()
	{
	delete [] mItems;
	}

	void QueType::MakeEmpty()
	{
	mFront = mMaxQue - 1;
	mRear = mMaxQue - 1;
	}

	bool QueType::IsEmpty() const
	// Returns true if the queue is empty; false otherwise.
	{
	return (mRear == mFront);
	}

	bool QueType::IsFull() const
	// Returns true if the queue is full; false otherwise.
	{
	return ((mRear + 1) % mMaxQue == mFront);
	}

	void QueType::Enqueue(ItemType newItem)
	// Post: If (queue is not full) newItem is at the mRear of the queue;
	//       otherwise a FullQueue exception is thrown.  
	{
		if (IsFull())
		{
			throw FullQueue();
		}
		else
		{
			mRear = (mRear + 1) % mMaxQue;
			mItems[mRear] = newItem;
		}
	}

	void QueType::Dequeue(ItemType& item)
	// Post: If (queue is not empty) the mFront of the queue has been 
	//       removed and a copy returned in item; 
	//       othersiwe a EmptyQueue exception has been thrown.
	{
		if (IsEmpty())
		{
			throw EmptyQueue();
		}
		else
		{
			mFront = (mFront + 1) % mMaxQue;
			item = mItems[mFront];
	}
	}

	void QueType::ReplaceItem(const ItemType& oldItem, const ItemType& newItem)
	{
		if (IsEmpty())
		{
			return;
		}

		for (unsigned int item = (mFront + 1) % mMaxQue; item != (mRear + 1) % mMaxQue; item = (item + 1) % mMaxQue)
		{
			if (mItems[item] == oldItem)
			{
				mItems[item] = newItem;
			}
		}
	}

	bool QueType::Identical(const QueType& other) const
	{
		if (this == &other)
		{
			return true;
		}

		if (IsEmpty() && other.IsEmpty())
		{
			return true;
		}

		unsigned int item = (mFront + 1) % mMaxQue;
		for (unsigned int otherItem = (other.mFront + 1) % other.mMaxQue;
			otherItem != (other.mRear + 1) % other.mMaxQue;
			otherItem = (otherItem + 1) % other.mMaxQue)
		{
			if (mItems[item] == other.mItems[otherItem])
			{
				unsigned int searchIndex;
				unsigned int otherSearchIndex;
				for (searchIndex = (item == mRear) ? (mFront + 1) % mMaxQue : (item + 1) % mMaxQue,
					otherSearchIndex = (otherItem == other.mRear) ? (other.mFront + 1) % other.mMaxQue : (otherItem + 1) % other.mMaxQue;
					searchIndex != item && otherSearchIndex != otherItem && mItems[searchIndex] == other.mItems[otherSearchIndex];
					searchIndex = (searchIndex == mRear) ? (mFront + 1) % mMaxQue : (searchIndex + 1) % mMaxQue, 
					otherSearchIndex = (otherSearchIndex == other.mRear) ? (other.mFront + 1) % other.mMaxQue : (otherSearchIndex + 1) % other.mMaxQue)
				{
				}

				if (searchIndex == item && otherSearchIndex == otherItem)
				{
					return true;
				}
			}
		}

		return false;
	}

	unsigned int QueType::Length() const
	{
		if (mRear < mFront)
		{
			return (mRear + mMaxQue - mFront);
		}
		else
		{
			return (mRear - mFront);
		}
	}
}

namespace lab5_6
{
	QueType::QueType(unsigned int capacity)
		: mCapacity(capacity)
		, mLength(0)
		, mFront(mCapacity - 1)
		, mRear(0)
		, mItems(new ItemType[mCapacity])
		, mMinIndex(-1)
	{
	}

	QueType::QueType()
		: mCapacity(500)
		, mLength(0)
		, mFront(mCapacity - 1)
		, mRear(0)
		, mItems(new ItemType[mCapacity])
		, mMinIndex(-1)
	{
	}

	QueType::~QueType()
	{
		delete [] mItems;
	}

	void QueType::MakeEmpty()
	{
		mFront = mCapacity - 1;
		mRear = 0;
		mLength = 0;
		mMinIndex = -1;
	}

	bool QueType::IsEmpty() const
	{
		return (mRear == ((mFront + 1) % mCapacity)) && (mLength == 0);
	}

	bool QueType::IsFull() const
	{
		return (mRear == ((mFront + 1) % mCapacity)) && (mLength == mCapacity);
	}

	void QueType::Enqueue(ItemType newItem)
	{
		if (IsFull())
		{
			throw FullQueue();
		}
		else
		{
			mItems[mRear] = newItem;

			if (mMinIndex != -1)
			{
				mMinIndex = (newItem <= mItems[mMinIndex]) ? mRear : mMinIndex; 
			}
			else
			{
				mMinIndex = mRear;
			}
			

			mRear = (mRear + 1) % mCapacity;
			++mLength;
		}
	}

	void QueType::Dequeue(ItemType& itemToDequeue)
	{
		if (IsEmpty())
		{
			throw EmptyQueue();
		}
		else
		{
			mFront = (mFront + 1) % mCapacity;
			itemToDequeue = mItems[mFront];
			--mLength;

			if (mLength > 0)
			{
				if (mFront == static_cast<unsigned int>(mMinIndex))
				{
					ItemType minimum = mItems[(mFront + 1) % mCapacity];
					for (unsigned int item = (mFront + 1) % mCapacity; item != mRear; item = (item + 1) % mCapacity)
					{
						if (mItems[item] <= minimum)
						{
							minimum = mItems[item];
							mMinIndex = item;
						}
					}
				}
			}
			else
			{
				mMinIndex = -1;
			}
		}
	}

	void QueType::MinDequeue(ItemType& itemToDequeue)
	{
		if (IsEmpty())
		{
			throw EmptyQueue();
		}
		else
		{
			itemToDequeue = mItems[mMinIndex];

			for (unsigned int item = mMinIndex;
				 item != (mFront + 1) % mCapacity;
				 item = (item - 1) % mCapacity)
			{
				mItems[item] = mItems[(item - 1) % mCapacity];
			}
			mFront = (mFront + 1) % mCapacity;
			--mLength;

			if (mLength > 0)
			{
				ItemType minimum = mItems[(mFront + 1) % mCapacity];
				for (unsigned int item = (mFront + 1) % mCapacity; item != mRear; item = (item + 1) % mCapacity)
				{
					if (mItems[item] <= minimum)
					{
						minimum = mItems[item];
						mMinIndex = item;
					}
				}
			}
			else
			{
				mMinIndex = -1;
			}
			
		}
	}
}