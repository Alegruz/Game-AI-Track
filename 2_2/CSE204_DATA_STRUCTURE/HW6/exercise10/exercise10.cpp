#include "SortedType.h"
#include "UnsortedType.h"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

template <class ItemType>
void SplitLists(SortedType<ItemType>& list, SortedType<ItemType>& list1, SortedType<ItemType>& list2, const ItemType& divider);

template <class ItemType>
void SplitLists(UnsortedType<ItemType>& list, UnsortedType<ItemType>& list1, UnsortedType<ItemType>& list2, const ItemType& divider);

int main()
{
	srand( time(NULL) );

	SortedType<int> st;
	UnsortedType<int> ust;
	size_t sortedTypeSize = rand() % 10;
	size_t unsortedTypeSize = rand() % 10;

	for (size_t count = 0; count < sortedTypeSize; ++count)
	{
		st.InsertItem(rand() % 10);
	}

	for (size_t count = 0; count < unsortedTypeSize; ++count)
	{
		ust.InsertItem(rand() % 10);
	}

	std::cout << st << std::endl;
	std::cout << ust << std::endl;

	int divider = rand() % 10;
	std::cout << "Divider = " << divider << std::endl;
	
	SortedType<int> mSpSt1;
	SortedType<int> mSpSt2;
	SortedType<int> cSpSt1;
	SortedType<int> cSpSt2;
	st.SplitLists(mSpSt1, mSpSt2, divider);
	SplitLists(st, cSpSt1, cSpSt2, divider);
	
	mSpSt1.ResetList();
	mSpSt2.ResetList();
	cSpSt1.ResetList();
	cSpSt2.ResetList();
	int mItem;
	int cItem;
	for (unsigned int count = 0; count < mSpSt1.LengthIs(); ++count)
	{
		mSpSt1.GetNextItem(mItem);
		cSpSt1.GetNextItem(cItem);
		assert( mItem == cItem );
	}

	for (unsigned int count = 0; count < mSpSt2.LengthIs(); ++count)
	{
		mSpSt2.GetNextItem(mItem);
		cSpSt2.GetNextItem(cItem);
		assert( mItem == cItem );
	}

	std::cout << "List1\n" << mSpSt1 << std::endl;
	std::cout << "List2\n" << mSpSt2 << std::endl;
	std::cout << "List1\n" << cSpSt1 << std::endl;
	std::cout << "List2\n" << cSpSt2 << std::endl;

	UnsortedType<int> mSpUst1;
	UnsortedType<int> mSpUst2;
	UnsortedType<int> cSpUst1;
	UnsortedType<int> cSpUst2;
	ust.SplitLists(mSpUst1, mSpUst2, divider);
	SplitLists(ust, cSpUst1, cSpUst2, divider);

	mSpUst1.ResetList();
	mSpUst2.ResetList();
	cSpUst1.ResetList();
	cSpUst2.ResetList();
	for (unsigned int count = 0; count < mSpUst1.LengthIs(); ++count)
	{
		mSpUst1.GetNextItem(mItem);
		cSpUst1.GetNextItem(cItem);
		assert( mItem == cItem );
	}

	for (unsigned int count = 0; count < mSpUst2.LengthIs(); ++count)
	{
		mSpUst2.GetNextItem(mItem);
		cSpUst2.GetNextItem(cItem);
		assert( mItem == cItem );
	}

	std::cout << "List1\n" << mSpUst1 << std::endl;
	std::cout << "List2\n" << mSpUst2 << std::endl;

	return 0;
}

template <class ItemType>
void SplitLists(SortedType<ItemType>& list, SortedType<ItemType>& list1, SortedType<ItemType>& list2, const ItemType& divider)
{
	unsigned int listLength = list.LengthIs();
	if (listLength == 0)
	{
		return;
	}
	
	list1.MakeEmpty();
	list2.MakeEmpty();

	list.ResetList();
	ItemType item;

	unsigned int count = 0;
	list.GetNextItem(item);
	for (; count < listLength && item <= divider; ++count)
	{
		list1.InsertItem(item);
		list.GetNextItem(item);
	}

	for (; count < listLength; ++count)
	{
		list2.InsertItem(item);
		list.GetNextItem(item);
	}
}

template <class ItemType>
void SplitLists(UnsortedType<ItemType>& list, UnsortedType<ItemType>& list1, UnsortedType<ItemType>& list2, const ItemType& divider)
{
	unsigned int listLength = list.LengthIs();
	if (listLength == 0)
	{
		return;
	}
	
	list1.MakeEmpty();
	list2.MakeEmpty();

	list.ResetList();
	ItemType item;

	for (unsigned int count = 0; count < listLength; ++count)
	{
		list.GetNextItem(item);
		if (item <= divider)
		{
			list1.InsertItem(item);
		}
		else
		{
			list2.InsertItem(item);
		}
	}
}