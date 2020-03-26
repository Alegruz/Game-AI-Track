#include "unsorted.h"

#include <cassert>
#include <iostream>

int main()
{
	UnsortedType unsortedList;
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
	unsortedList.InsertItem(item6);
	unsortedList.InsertItem(item2);
	unsortedList.InsertItem(item5);
	unsortedList.InsertItem(item4);

	unsortedList.ResetList();
	ItemType itemToPrint;
	for (size_t itemIndex = 0; itemIndex < unsortedList.LengthIs(); ++itemIndex)
	{
		unsortedList.GetNextItem(itemToPrint);
		itemToPrint.Print(std::cout);
		std::cout << " ";
	}
	std::cout << "size: " << unsortedList.LengthIs() << std::endl;
	assert(unsortedList.LengthIs() == 4);
	assert(unsortedList.IsFull() == false);

	unsortedList.DeleteItem(item6);

	unsortedList.ResetList();
	for (size_t itemIndex = 0; itemIndex < unsortedList.LengthIs(); ++itemIndex)
	{
		unsortedList.GetNextItem(itemToPrint);
		itemToPrint.Print(std::cout);
		std::cout << " ";
	}
	std::cout << "size: " << unsortedList.LengthIs() << std::endl;

	unsortedList.DeleteItem(item6);

	unsortedList.ResetList();
	for (size_t itemIndex = 0; itemIndex < unsortedList.LengthIs(); ++itemIndex)
	{
		unsortedList.GetNextItem(itemToPrint);
		itemToPrint.Print(std::cout);
		std::cout << " ";
	}
	std::cout << "size: " << unsortedList.LengthIs() << std::endl;
	assert(unsortedList.LengthIs() == 3);
	assert(unsortedList.IsFull() == false);

	unsortedList.InsertItem(item6);
	unsortedList.InsertItem(item6);

	unsortedList.ResetList();
	for (size_t itemIndex = 0; itemIndex < unsortedList.LengthIs(); ++itemIndex)
	{
		unsortedList.GetNextItem(itemToPrint);
		itemToPrint.Print(std::cout);
		std::cout << " ";
	}
	std::cout << "size: " << unsortedList.LengthIs() << std::endl;
	assert(unsortedList.LengthIs() == 5);
	assert(unsortedList.IsFull() == true);

	unsortedList.DeleteItem(item6);

	unsortedList.ResetList();
	for (size_t itemIndex = 0; itemIndex < unsortedList.LengthIs(); ++itemIndex)
	{
		unsortedList.GetNextItem(itemToPrint);
		itemToPrint.Print(std::cout);
		std::cout << " ";
	}
	std::cout << "size: " << unsortedList.LengthIs() << std::endl;
	assert(unsortedList.LengthIs() == 3);
	assert(unsortedList.IsFull() == false);

	return 0;
}