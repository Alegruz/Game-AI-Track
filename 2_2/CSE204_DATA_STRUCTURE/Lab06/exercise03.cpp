#include "SortedType.h"
#include "UnsortedType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace exercise03;

template <class ItemType>
void MergeLists(SortedType<ItemType>& list1, SortedType<ItemType>& list2, SortedType<ItemType>& result);

template <class ItemType>
void MergeLists(UnsortedType<ItemType>& list1, UnsortedType<ItemType>& list2, UnsortedType<ItemType>& result);

int main()
{
	srand ( time(NULL) );

	SortedType<int> st1;
	SortedType<int> st2;
	SortedType<int> st3;
	size_t listSize1 = rand() % 10;
	size_t listSize2 = rand() % 10;
	bool bItemExists;
	int item;
	for (size_t index = 0; index < listSize1; ++index)
	{
		item = rand() % 10;
		st1.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		st1.InsertItem(item);
	}
	for (size_t index = 0; index < listSize2; ++index)
	{
		item = rand() % 10;
		st2.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		st2.InsertItem(item);
	}
	std::cout << st1 << std::endl;
	std::cout << st2 << std::endl;
	
	st1.MergeLists(st2, st3);

	std::cout << "\nMerge Result\n" << st3 << std::endl;

	std::cout << "--------------------------" << std::endl;
	st1.MakeEmpty();
	st2.MakeEmpty();
	st3.MakeEmpty();
	for (size_t index = 0; index < listSize1; ++index)
	{
		item = rand() % 10;
		st1.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		st1.InsertItem(item);
	}
	for (size_t index = 0; index < listSize2; ++index)
	{
		item = rand() % 10;
		st2.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		st2.InsertItem(item);
	}
	std::cout << st1 << std::endl;
	std::cout << st2 << std::endl;
	
	MergeLists(st1, st2, st3);

	std::cout << "\nMerge Result\n" << st3 << std::endl;

	UnsortedType<int> ust1;
	UnsortedType<int> ust2;
	UnsortedType<int> ust3;
	listSize1 = rand() % 10;
	listSize2 = rand() % 10;
	for (size_t index = 0; index < listSize1; ++index)
	{
		item = rand() % 10;
		ust1.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		ust1.InsertItem(item);
	}
	for (size_t index = 0; index < listSize2; ++index)
	{
		item = rand() % 10;
		ust2.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		ust2.InsertItem(item);
	}
	std::cout << ust1 << std::endl;
	std::cout << ust2 << std::endl;
	
	ust1.MergeLists(ust2, ust3);

	std::cout << "\nMerge Result\n" << ust3 << std::endl;

	std::cout << "--------------------------" << std::endl;
	ust1.MakeEmpty();
	ust2.MakeEmpty();
	ust3.MakeEmpty();
	for (size_t index = 0; index < listSize1; ++index)
	{
		item = rand() % 10;
		ust1.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		ust1.InsertItem(item);
	}
	for (size_t index = 0; index < listSize2; ++index)
	{
		item = rand() % 10;
		ust2.RetrieveItem(item, bItemExists);
		if (bItemExists)
		{
			--index;
			continue;
		}
		ust2.InsertItem(item);
	}
	std::cout << ust1 << std::endl;
	std::cout << ust2 << std::endl;
	
	MergeLists(ust1, ust2, ust3);

	std::cout << "\nMerge Result\n" << ust3 << std::endl;

	return 0;
}

template <class ItemType>
void MergeLists(SortedType<ItemType>& list1, SortedType<ItemType>& list2, SortedType<ItemType>& result)
{
	list1.ResetList();
	list2.ResetList();
	ItemType item1;
	ItemType item2;
	list1.GetNextItem(item1);
	list2.GetNextItem(item2);
	unsigned int count1 = list1.LengthIs();
	unsigned int count2 = list2.LengthIs();

	while (count1 > 0 && count2 > 0)
	{
		if (item1 < item2)
		{
			result.InsertItem(item1);
			list1.GetNextItem(item1);
			--count1;
		}
		else
		{
			result.InsertItem(item2);
			list2.GetNextItem(item2);
			--count2;
		}
	}

	while (count1 > 0)
	{
		result.InsertItem(item1);
		list1.GetNextItem(item1);
		--count1;
	}

	while (count2 > 0)
	{
		result.InsertItem(item2);
		list2.GetNextItem(item2);
		--count2;
	}
}

template <class ItemType>
void MergeLists(UnsortedType<ItemType>& list1, UnsortedType<ItemType>& list2, UnsortedType<ItemType>& result)
{
	list1.ResetList();
	list2.ResetList();
	UnsortedType<ItemType> tempList;
	ItemType item;

	for (unsigned int count = 0; count < list1.LengthIs(); ++count)
	{
		list1.GetNextItem(item);
		tempList.InsertItem(item);
	}

	for (unsigned int count = 0; count < list2.LengthIs(); ++count)
	{
		list2.GetNextItem(item);
		tempList.InsertItem(item);
	}

	tempList.ResetList();
	for (unsigned int count = 0; count < tempList.LengthIs(); ++count)
	{
		tempList.GetNextItem(item);
		result.InsertItem(item);
	}
}