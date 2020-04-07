// Implementation file for sorted.h
#include "SortedType.h"

SortedType::SortedType()
	: mLength(0), mCurrentPos(-1)
{
}
bool SortedType::IsFull() const
{
	return (mLength == MAX_ITEMS);
}

int SortedType::LengthIs() const
{
	return mLength;
}

bool SortedType::RetrieveItem(HouseType& item) 
{
	unsigned int head = 0;
	unsigned int tail = mLength - 1;
	unsigned int middle;

	while (head <= tail)
	{
		middle = (head + tail) / 2;
		if (mInfo[middle] > item)
		{
			if (middle == 0)
			{
				break;
			}
			tail = middle - 1;
		}
		else if (mInfo[middle] < item)
		{
			head = middle + 1;
		}
		else
		{
			item = mInfo[middle];
			return true;
		}
	}

	return false;
}

void SortedType::DeleteItem(HouseType& item) 
{
	unsigned int location;

	for (location = 0; location < mLength; ++location)
	{
		if (item == mInfo[location])
		{
			mInfo[location] = mInfo[location + 1];
			--location;
			--mLength;
		}

	}
}

void SortedType::InsertItem(HouseType& item) 
{
	unsigned int location;

	for (location = 0; location < mLength && item >= mInfo[location]; ++location)
	{
	}

	for (unsigned int index = mLength; index > location; index--)
	{
		mInfo[index] = mInfo[index - 1];
	}

	mInfo[location] = item;
	mLength++;
}

void SortedType::ResetList()
// Post: mCurrentPos has been initialized.
{
  mCurrentPos = -1;
}

void SortedType::GetNextItem(HouseType& item)
// Post: item is current item.
//       Current position has been updated.
{
  mCurrentPos++;
  item = mInfo[mCurrentPos];
}

