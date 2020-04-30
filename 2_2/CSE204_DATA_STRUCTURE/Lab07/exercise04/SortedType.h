#pragma once

#include <iostream>
#include <new>

template<class ItemType>
struct NodeType
{
    ItemType mInfo;
    NodeType* mNext;
};

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
	void PrintReverse();
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

    for (size_t node = 0; node < mLength; ++node)
    {
        tempPtr = mListData;
        mListData = mListData->mNext;
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
		if (location->mInfo < item)
		{
			location = location->mNext;
			moreToSearch = (location != nullptr);
		}
		else if (item == location->mInfo)
		{
			found = true;
			item = location->mInfo;
		}
		else
		{
			moreToSearch = false;
		}
	}
}

// template <class ItemType>
// void SortedType<ItemType>::InsertItem(ItemType item)
// {
// 	NodeType<ItemType>* newNode;  // pointer to node being inserted
// 		NodeType<ItemType>* predLoc;  // trailing pointer
// 		NodeType<ItemType>* location; // traveling pointer
// 		bool moreToSearch;

// 		location = mListData;
// 		predLoc = nullptr;
// 		moreToSearch = (location != nullptr);

// 		// Find insertion point.
// 		while (moreToSearch)
// 		{
// 			if (location->mInfo < item)
// 			{
// 				predLoc = location;
// 				location = location->mNext;
// 				moreToSearch = (location != nullptr);
// 			}
// 			else
// 			{
// 				moreToSearch = false;
// 			}
// 		}

// 		// Prepare node for insertion
// 		newNode = new NodeType<ItemType>;
// 		newNode->mInfo = item;
// 		// Insert node into list.
// 		if (predLoc == nullptr)         // Insert as first
// 		{
// 			newNode->mNext = mListData;
// 			mListData = newNode;
// 		}
// 		else
// 		{
// 			newNode->mNext = location;
// 			predLoc->mNext = newNode;
// 		}
// 		++mLength;
// }

// template <class ItemType>
// void SortedType<ItemType>::DeleteItem(ItemType item)
// {
//     NodeType<ItemType>* location = mListData;
//     NodeType<ItemType>* tempLocation;

//     // Locate node to be deleted.
//     if (item == mListData->mInfo)
//     {
//         tempLocation = location;
//         mListData = mListData->mNext;		// Delete first node.
//     }
//     else
//     {
//         while (!(item==(location->mNext)->mInfo))
// 		{
//         	location = location->mNext;
// 		}

//         // Delete node at location->mNext
//         tempLocation = location->mNext;
//         location->mNext = (location->mNext)->mNext;
//     }
//     delete tempLocation;
//     mLength--;
// }

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

	item = mCurrentPos->mInfo; 
	mCurrentPos = mCurrentPos->mNext;
} 

template <class ItemType>
SortedType<ItemType>::~SortedType()
{
    NodeType<ItemType>* tempPtr;

    for (size_t node = 0; node < mLength; ++node)
    {
        tempPtr = mListData;
        mListData = mListData->mNext;
        delete tempPtr;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SortedType<T>& other)
{
	NodeType<T>* tempPtr = other.mListData;
	for (size_t index = 0; index < other.mLength; ++index)
	{
		os << "SortedList[" << index << "] = " << tempPtr->mInfo << std::endl;
		tempPtr = tempPtr->mNext;
	}

	return os;
}

template<class ItemType>
void FindItem(NodeType<ItemType>* mListData, 
              ItemType item,
              NodeType<ItemType>*& location, 
              NodeType<ItemType>*& predLoc,
              bool& found)
{
  bool moreToSearch = true;

  location = mListData->mNext;
  predLoc = mListData;
  found = false;

  while (moreToSearch && !found)
  {
    if (item < location->mInfo)
      moreToSearch = false;
    else if (item == location->mInfo)
      found = true;
    else
    {
      predLoc = location;
      location = location->mNext;
      moreToSearch = (location != mListData->mNext);
    }
  }
}

template<class ItemType>
void SortedType<ItemType>::InsertItem(ItemType item)
{
  NodeType<ItemType>* newNode;
  NodeType<ItemType>* predLoc;
  NodeType<ItemType>* location;
  bool found;
  
  newNode = new NodeType<ItemType>;
  newNode->mInfo = item;
  if (mListData != nullptr)
  {
    FindItem(mListData, item, location, predLoc, found);
    newNode->mNext = predLoc->mNext;
    predLoc->mNext = newNode;
    // If this is last node in list, reassign mListData.
    if (mListData->mInfo < item)
      mListData = newNode;
  }
  else // Inserting into an empty list.
  {
    mListData = newNode;
    newNode->mNext = newNode;
  }
  mLength++;
}

template<class ItemType>
void SortedType<ItemType>::DeleteItem(ItemType item)
{
  NodeType<ItemType>* location;
  NodeType<ItemType>* predLoc;
  bool found;
  
  FindItem(mListData, item, location, predLoc, found);
  if (predLoc == location) // Only node in list?
    mListData = nullptr;
  else
  {
    predLoc->mNext = location->mNext;
    if (location == mListData) // Deleting last node in list?
      mListData = predLoc;
  }
  delete location;
  mLength--;
}

template<class ItemType>
void SortedType<ItemType>::PrintReverse()
{
	NodeType<ItemType>* tempPtr  = nullptr;

	for (size_t node = 0; node < mLength; ++node)
	{
		tempPtr = mListData;
		for (size_t index = 0; index < mLength - node; ++index)
		{
			tempPtr = tempPtr->mNext;
		}
		std::cout << tempPtr->mInfo << std::endl;
	}
}