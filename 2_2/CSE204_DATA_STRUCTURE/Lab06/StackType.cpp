#include "StackType.h"

#include <cstddef>
#include <new>

namespace exercise01
{
	StackType::StackType()
		: mTopPtr(nullptr)
	{
	}

	StackType::~StackType()
	{
		NodeType* tempPtr;

		while (mTopPtr != nullptr)
		{
			tempPtr = mTopPtr;
			mTopPtr = mTopPtr->mNext;
			delete tempPtr;
		}
	}

	void StackType::Push(ItemType newItem)
	{
		if (IsFull())
		{
			throw FullStack();
		}
		else
		{
			NodeType* location;
			location = new NodeType;
			location->mInfo = newItem;
			location->mNext = mTopPtr;
			mTopPtr = location;
		}
	}
	void StackType::Pop()
	{
		if (IsEmpty())
		{
		throw EmptyStack();
		}
		else
		{  
			NodeType* tempPtr;
			tempPtr = mTopPtr;
			mTopPtr = mTopPtr->mNext;
			delete tempPtr;
		}
	}

	ItemType StackType::Top()
	{
		if (IsEmpty())
		{
			throw EmptyStack();
		}
		else
		{
			return mTopPtr->mInfo;
		}
	}

	bool StackType::IsEmpty() const
	{
		return (mTopPtr == nullptr);
	}

	bool StackType::IsFull() const
	{
		NodeType* location;

		try
		{
			location = new NodeType;
			delete location;
			return false;
		}
		catch(std::bad_alloc)
		{
			return true;
		}
	}

	void StackType::ReplaceItem(const ItemType& oldItem, const ItemType& newItem)
	{
		if (mTopPtr == nullptr)
		{
			return;
		}

		NodeType* tempPtr = mTopPtr;
		while (tempPtr != nullptr)
		{
			if (tempPtr->mInfo == oldItem)
			{
				tempPtr->mInfo = newItem;
			}

			tempPtr = tempPtr->mNext;
		}
	}

	std::ostream& operator<<(std::ostream& os, const StackType& other)
	{
		NodeType* tempPtr = other.mTopPtr;
		size_t index = 0;
		while (tempPtr != nullptr)
		{
			os << "Stack[" << index << "] = " << tempPtr->mInfo << std::endl;
			tempPtr = tempPtr->mNext;
			++index;
		}

		return os;
	}
}