#pragma once

#include "NodeType.h"

#include <iostream>
#include <new>

template <class ItemType>
class SortedType
{
template <typename T>
friend std::ostream& operator<<(std::ostream& os, const SortedType<T>& other);
public:
	SortedType();
	~SortedType();

	bool IsFull() const;
	unsigned int  LengthIs() const;
	void MakeEmpty();
	void RetrieveItem(ItemType& item, bool& found);
	void InsertItem(ItemType item); 
	void DeleteItem(ItemType item);
	void ResetList();
	void GetNextItem(ItemType&);
	void SplitLists(SortedType& list1, SortedType& list2, const ItemType& item);

private:
	NodeType<ItemType>* mListData;
	unsigned int mLength;
	NodeType<ItemType>* mCurrentPos;
};

template <class ItemType>
SortedType<ItemType>::SortedType()  // Class constructor
{
	mLength = 0;
	mListData = nullptr;
}

template<class ItemType>
bool SortedType<ItemType>::IsFull() const
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
unsigned int SortedType<ItemType>::LengthIs() const
{
  return mLength;
}

template <class ItemType>
void SortedType<ItemType>::MakeEmpty()
{
    NodeType<ItemType>* tempPtr;

    while (mListData != nullptr)
    {
        tempPtr = mListData;
        mListData = mListData->next;
        delete tempPtr;
    }

    mLength = 0;
}

template <class ItemType>
void SortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
	bool moreToSearch;
	NodeType<ItemType>* location;

	location = mListData;
	found = false;
	moreToSearch = (location != nullptr);

	while (moreToSearch && !found)
	{
		if (location->info < item)
		{
			location = location->next;
			moreToSearch = (location != nullptr);
		}
		else if (item == location->info)
		{
			found = true;
			item = location->info;
		}
		else
		{
			moreToSearch = false;
		}
	}
}

template <class ItemType>
void SortedType<ItemType>::InsertItem(ItemType item)
{
	NodeType<ItemType>* newNode;  // pointer to node being inserted
		NodeType<ItemType>* predLoc;  // trailing pointer
		NodeType<ItemType>* location; // traveling pointer
		bool moreToSearch;

		location = mListData;
		predLoc = nullptr;
		moreToSearch = (location != nullptr);

		// Find insertion point.
		while (moreToSearch)
		{
			if (location->info < item)
			{
				predLoc = location;
				location = location->next;
				moreToSearch = (location != nullptr);
			}
			else
			{
				moreToSearch = false;
			}
		}

		// Prepare node for insertion
		newNode = new NodeType<ItemType>;
		newNode->info = item;
		// Insert node into list.
		if (predLoc == nullptr)         // Insert as first
		{
			newNode->next = mListData;
			mListData = newNode;
		}
		else
		{
			newNode->next = location;
			predLoc->next = newNode;
		}
		++mLength;
}

template <class ItemType>
void SortedType<ItemType>::DeleteItem(ItemType item)
{
    NodeType<ItemType>* location = mListData;
    NodeType<ItemType>* tempLocation;

    // Locate node to be deleted.
    if (item == mListData->info)
    {
        tempLocation = location;
        mListData = mListData->next;		// Delete first node.
    }
    else
    {
        while (!(item==(location->next)->info))
		{
        	location = location->next;
		}

        // Delete node at location->next
        tempLocation = location->next;
        location->next = (location->next)->next;
    }
    delete tempLocation;
    mLength--;
}

template <class ItemType>
void SortedType<ItemType>::ResetList()
{
	mCurrentPos = nullptr;
}
 
template <class ItemType>
void SortedType<ItemType>::GetNextItem(ItemType& item)
{
	if (mListData == nullptr)
	{
		return;
	}

	if (mCurrentPos == nullptr)
	{
		mCurrentPos = mListData;
	}

	item = mCurrentPos->info; 
	mCurrentPos = mCurrentPos->next;
} 

template <class ItemType>
SortedType<ItemType>::~SortedType()
{
    NodeType<ItemType>* tempPtr;

    while (mListData != nullptr)
    {
        tempPtr = mListData;
        mListData = mListData->next;
        delete tempPtr;
    }
}

template <class ItemType>
void SortedType<ItemType>::SplitLists(SortedType& list1, SortedType& list2, const ItemType& item)
{
	NodeType<ItemType>* tempPtr = mListData;

	if (tempPtr == nullptr)
	{
		return;
	}

	list1.MakeEmpty();
	list2.MakeEmpty();

	for (; tempPtr != nullptr && tempPtr->info <= item; tempPtr = tempPtr->next)
	{
		list1.InsertItem(tempPtr->info);	
	}

	for (; tempPtr != nullptr; tempPtr = tempPtr->next)
	{
		list2.InsertItem(tempPtr->info);
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SortedType<T>& other)
{
	NodeType<T>* tempPtr = other.mListData;
	size_t index = 0;
	while (tempPtr != nullptr)
	{
		os << "SortedList[" << index << "] = " << tempPtr->info << std::endl;
		tempPtr = tempPtr->next;
		++index;
	}

	return os;
}