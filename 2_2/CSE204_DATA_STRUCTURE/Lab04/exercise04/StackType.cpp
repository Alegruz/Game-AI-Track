#include "StackType.h"

#include <iostream>

StackType::StackType()
	: mTop(0)
{
}

bool StackType::IsEmpty() const
{
	return (mTop == 0);
}

bool StackType::IsFull() const
{
	return (mTop ==  MAX_ITEMS);
}

void StackType::Push(const ItemType& newItem)
{
	if(IsFull())
    {
		throw FullStack();
	}

	mItems[mTop++] = newItem;
}

void StackType::Pop()
{
	if(IsEmpty())
    {
		throw EmptyStack();
	}

	--mTop;
}

const ItemType& StackType::Top() const
{
	if (IsEmpty())
    {
		throw EmptyStack();
	}

	return mItems[mTop - 1];
}    

void StackType::ReplaceItem(const ItemType& oldItem, const ItemType& newItem)
{
	for (size_t item = 0; item < mTop; ++item)
	{
		if (mItems[item] == oldItem)
		{
			mItems[item] = newItem;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const StackType& rhs)
{
	for (size_t item = 0; item < rhs.mTop; ++item)
	{
		os << "item[" << item << "] = " << rhs.mItems[item] << std::endl;
	}

	return os;
}