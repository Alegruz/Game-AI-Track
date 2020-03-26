#include "sorted.h"

#include <iostream>

void MergeList(SortedType list1, SortedType list2, SortedType& result);

int main()
{
	SortedType sortedList1;
	SortedType sortedList2;
	ItemType item1;
	ItemType item2;
	ItemType item3;
	ItemType item4;
	ItemType item5;
	ItemType item6;

	item1.Initialize(1);
	item2.Initialize(22);
	item3.Initialize(3);
	item4.Initialize(44);
	item5.Initialize(5);
	item6.Initialize(66);

	std::cout << "INSERT ITEM" << std::endl;
	sortedList1.InsertItem(item6);
	sortedList1.InsertItem(item2);
	sortedList1.InsertItem(item5);
	sortedList1.InsertItem(item4);

	sortedList2.InsertItem(item3);
	sortedList2.InsertItem(item1);

	std::cout << "MERGE LIST" << std::endl;
	SortedType sortedList3;
	MergeList(sortedList1, sortedList2, sortedList3);

	sortedList3.ResetList();
	ItemType itemToPrint;
	for (size_t itemIndex = 0; itemIndex < sortedList3.LengthIs(); ++itemIndex)
	{
		sortedList3.GetNextItem(itemToPrint);
		itemToPrint.Print(std::cout);
		std::cout << std::endl;
	}

	return 0;
}

void MergeList(SortedType list1, SortedType list2, SortedType& result)
{
	// merge two sorted list and create third, new sorted list
	// list1 and list2 are all initialized by ComparedTo. list1 and list2 doensn't share the same key
	// result is a sorted list with both characteristics from list1 and list2
	// a. write a Prototype
	// b. create the function
	// c. big-o notation
	list1.ResetList();
	ItemType item;
	for (size_t itemIndex = 0; itemIndex < list1.LengthIs(); ++itemIndex)
	{
		list1.GetNextItem(item);
		result.InsertItem(item);
	}
	list1.ResetList();

	if (list1.LengthIs() >= 5)
	{
		return;
	}

	list2.ResetList();
	for (size_t itemIndex = 0; itemIndex < list2.LengthIs(); ++itemIndex)
	{
		list2.GetNextItem(item);
		result.InsertItem(item);
	}
	list2.ResetList();
}