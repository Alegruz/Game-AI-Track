#pragma once

#include <iostream>
#include <new>

// Header file for Unsorted List ADT.
template <class ItemType>
struct NodeType;

// Assumption:  ItemType is a type for which the operators "<"
// and "==" are defined�either an appropriate built-in type or
// a class that overloads these operators.

template <class ItemType>
class UnsortedType
{
	template <typename T>
	friend std::ostream &operator<<(std::ostream &os, const UnsortedType<T> &other);

public:
	UnsortedType();
	~UnsortedType();

	bool IsFull() const;
	unsigned int LengthIs() const;
	void MakeEmpty();
	void RetrieveItem(ItemType &item, bool &found);
	void InsertItem(ItemType item);
	void DeleteItem(ItemType item);
	void ResetList();
	void GetNextItem(ItemType &item);
	void PrintSumSquare() const;

private:
	NodeType<ItemType> *mListData;
	unsigned int mLength;
	NodeType<ItemType> *mCurrentPos;
};

template <class ItemType>
struct NodeType
{
	ItemType info;
	NodeType *next;
};

template <class ItemType>
ItemType Sumsquares_a(NodeType<ItemType> *list);
template <class ItemType>
ItemType Sumsquares_b(NodeType<ItemType> *list);
template <class ItemType>
ItemType Sumsquares_c(NodeType<ItemType> *list);
template <class ItemType>
ItemType Sumsquares_d(NodeType<ItemType> *list);
template <class ItemType>
ItemType Sumsquares_e(NodeType<ItemType> *list);

template <class ItemType>
UnsortedType<ItemType>::UnsortedType() // Class constructor
{
	mLength = 0;
	mListData = nullptr;
}

template <class ItemType>
UnsortedType<ItemType>::~UnsortedType()
// Class destructor
{
	MakeEmpty();
}
template <class ItemType>
bool UnsortedType<ItemType>::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
	NodeType<ItemType> *location;
	try
	{
		location = new NodeType<ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}
template <class ItemType>
unsigned int UnsortedType<ItemType>::LengthIs() const
// Post: Number of items in the list is returned.
{
	return mLength;
}
template <class ItemType>
void UnsortedType<ItemType>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	NodeType<ItemType> *tempPtr;

	while (mListData != nullptr)
	{
		tempPtr = mListData;
		mListData = mListData->next;
		delete tempPtr;
	}
	mLength = 0;
}
template <class ItemType>
void UnsortedType<ItemType>::RetrieveItem(ItemType &item,
										  bool &found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged.
{
	bool moreToSearch;
	NodeType<ItemType> *location;

	location = mListData;
	found = false;
	moreToSearch = (location != nullptr);

	while (moreToSearch && !found)
	{
		if (item == location->info)
		{
			found = true;
			item = location->info;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != nullptr);
		}
	}
}
template <class ItemType>
void UnsortedType<ItemType>::InsertItem(ItemType item)
// item is in the list; mLength has been incremented.
{
	NodeType<ItemType> *location;

	location = new NodeType<ItemType>;
	location->info = item;
	location->next = mListData;
	mListData = location;
	mLength++;
}
template <class ItemType>
void UnsortedType<ItemType>::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
	NodeType<ItemType> *location = mListData;
	NodeType<ItemType> *tempLocation;

	// Locate node to be deleted.
	if (item == mListData->info)
	{
		tempLocation = location;
		mListData = mListData->next; // Delete first node.
	}
	else
	{
		while (!(item == (location->next)->info))
			location = location->next;

		// Delete node at location->next
		tempLocation = location->next;
		location->next = (location->next)->next;
	}
	delete tempLocation;
	mLength--;
}

template <class ItemType>
void UnsortedType<ItemType>::ResetList()
// Post: Current position has been initialized.
{
	mCurrentPos = nullptr;
}

template <class ItemType>
void UnsortedType<ItemType>::GetNextItem(ItemType &item)
// Post:  Current position has been updated; item is current item.
{
	if (mCurrentPos == nullptr)
		mCurrentPos = mListData;
	else
		mCurrentPos = mCurrentPos->next;
	item = mCurrentPos->info;
}

template <class ItemType>
void UnsortedType<ItemType>::PrintSumSquare() const
{
	std::cout << "A:" << std::endl << Sumsquares_a(mListData) << std::endl;
	std::cout << "B:" << std::endl << Sumsquares_b(mListData) << std::endl;
	std::cout << "C:" << std::endl << Sumsquares_c(mListData) << std::endl;
	std::cout << "D:" << std::endl << Sumsquares_d(mListData) << std::endl;
	std::cout << "E:" << std::endl << Sumsquares_e(mListData) << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const UnsortedType<T> &other)
{
	NodeType<T> *tempPtr = other.mListData;
	size_t index = 0;
	while (tempPtr != nullptr)
	{
		os << "UnsortedList[" << index << "] = " << tempPtr->info << std::endl;
		tempPtr = tempPtr->next;
		++index;
	}

	return os;
}

// template <class ItemType>
// ItemType Sumsquares_a(NodeType<ItemType> *list)
// {
// 	return 0;	// will only return 0 and the codes below will never run

// 	if (list != nullptr)
// 	{
// 		return (list->info * list->info) + Sumsquares_a(list->next);
// 	}
// }

template <class ItemType>
ItemType Sumsquares_a(NodeType<ItemType> *list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		return (list->info * list->info) + Sumsquares_a(list->next);
	}
}

// template <class ItemType>
// ItemType Sumsquares_b(NodeType<ItemType> *list)
// {
// 	unsigned int sum = 0;
// 	while (list != nullptr)
// 	{
// 		sum = list->info + sum;	// only adds the value of elements, not their square
// 		list = list->next;
// 	}

// 	return sum;
// }

template <class ItemType>
ItemType Sumsquares_b(NodeType<ItemType> *list)
{
	unsigned int sum = 0;
	while (list != nullptr)
	{
		sum = list->info * list->info + sum;
		list = list->next;
	}

	return sum;
}

template <class ItemType>
ItemType Sumsquares_c(NodeType<ItemType> *list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		return (list->info * list->info + Sumsquares_c(list->next));	// will properly work.
	}
}

// template <class ItemType>
// ItemType Sumsquares_d(NodeType<ItemType> *list)
// {
// 	if (list->next == nullptr)	// fails when list is nullptr
// 	{
// 		return (list->info * list->info);
// 	}
// 	else
// 	{
// 		return (list->info * list->info + Sumsquares_d(list->next));
// 	}
// }

template <class ItemType>
ItemType Sumsquares_d(NodeType<ItemType> *list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else if (list->next == nullptr)
	{
		return (list->info * list->info);
	}
	else
	{
		return (list->info * list->info + Sumsquares_d(list->next));
	}
}

// template <class ItemType>
// ItemType Sumsquares_e(NodeType<ItemType> *list)
// {
// 	if (list == nullptr)
// 	{
// 		return 0;
// 	}
// 	else
// 	{
// 		return (Sumsquares_e(list->next) * Sumsquares_e(list->next));	// every single call will eventually return only 0
// 	}
// }

template <class ItemType>
ItemType Sumsquares_e(NodeType<ItemType> *list)
{
	if (list == nullptr)
	{
		return 0;
	}
	else
	{
		return (list->info * list->info + Sumsquares_e(list->next));
	}
}