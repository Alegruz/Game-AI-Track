#pragma once

#include "NodeType.h"

#include <iostream>
#include <new>

template <class ItemType>
class UnsortedType
{
template <typename T>
friend std::ostream& operator<<(std::ostream& os, const UnsortedType<T>& other);
public:
	UnsortedType();
	~UnsortedType();

	bool IsFull() const;
	unsigned int  LengthIs() const;
	void MakeEmpty();
	void RetrieveItem(ItemType& item, bool& found);
	void InsertItem(ItemType item); 
	void DeleteItem(ItemType item);
	void ResetList();
	void GetNextItem(ItemType& item);
	void SplitLists(UnsortedType& list1, UnsortedType& list2, const ItemType& item);

private:
	NodeType<ItemType>* mListData;
	unsigned int mLength;
	NodeType<ItemType>* mCurrentPos;
};

template <class ItemType>
UnsortedType<ItemType>::UnsortedType()
{
	mLength = 0;
	mListData = nullptr;
}

template <class ItemType>
UnsortedType<ItemType>::~UnsortedType()
{
	MakeEmpty();
}

template<class ItemType>
bool UnsortedType<ItemType>::IsFull() const
{
	NodeType<ItemType>* location;

	try
	{
		location = new NodeType<ItemType>;
		delete location;
		return false;
	}
	catch(std::bad_alloc exception)
	{
		return true;
	}
}

template <class ItemType>
unsigned int UnsortedType<ItemType>::LengthIs() const
{
	return mLength;
}

template <class ItemType>
void UnsortedType<ItemType>::MakeEmpty()
{
    NodeType<ItemType>* tempPtr;

    while (mListData != nullptr)
    {
        tempPtr = mListData;
        mListData = mListData->mNext;
        delete tempPtr;
    }
    mLength = 0;
}

template <class ItemType>
void UnsortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
    bool moreToSearch;
    NodeType<ItemType>* location;

    location = mListData;
    found = false;
    moreToSearch = (location != nullptr);

    while (moreToSearch && !found)
    {
        if (item == location->mInfo)
        {
            found = true;
            item = location->mInfo;
        }
        else
        {
            location = location->mNext;
            moreToSearch = (location != nullptr);
        }
    }
}
template <class ItemType>
void UnsortedType<ItemType>::InsertItem(ItemType item)
{
    NodeType<ItemType>* location;

    location = new NodeType<ItemType>;
    location->mInfo = item;
    location->mNext = mListData;
    mListData = location;
    mLength++;
}

template <class ItemType>
void UnsortedType<ItemType>::DeleteItem(ItemType item)
{
    NodeType<ItemType>* location = mListData;
    NodeType<ItemType>* tempLocation;

    // Locate node to be deleted.
    if (item == mListData->mInfo)
    {
        tempLocation = location;
        mListData = mListData->mNext;		// Delete first node.
    }
    else
    {
        while (!(item==(location->mNext)->mInfo))
		{
            location = location->mNext;
		}

        // Delete node at location->mNext
        tempLocation = location->mNext;
        location->mNext = (location->mNext)->mNext;
    }
    delete tempLocation;
    mLength--;
}

template <class ItemType>
void UnsortedType<ItemType>::ResetList()
{
	mCurrentPos = nullptr;
}
 
template <class ItemType>
void UnsortedType<ItemType>::GetNextItem(ItemType& item)
{
	if (mListData == nullptr)
	{
		return;
	}

	if (mCurrentPos == nullptr)
	{
		mCurrentPos = mListData;
	}
	
	item = mCurrentPos->mInfo;
	mCurrentPos = mCurrentPos->mNext;
} 

template <class ItemType>
void UnsortedType<ItemType>::SplitLists(UnsortedType& list1, UnsortedType& list2, const ItemType& item)
{
	NodeType<ItemType>* tempPtr = mListData;
	
	if (tempPtr == nullptr)
	{
		return;
	}

	list1.MakeEmpty();
	list2.MakeEmpty();

	for (; tempPtr != nullptr; tempPtr = tempPtr->mNext)
	{
		if (tempPtr->mInfo <= item)
		{
			list1.InsertItem(tempPtr->mInfo);	
		}
		else
		{
			list2.InsertItem(tempPtr->mInfo);
		}
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const UnsortedType<T>& other)
{
	NodeType<T>* tempPtr = other.mListData;
	size_t index = 0;
	while (tempPtr != nullptr)
	{
		os << "UnsortedList[" << index << "] = " << tempPtr->mInfo << std::endl;
		tempPtr = tempPtr->mNext;
		++index;
	}

	return os;
}