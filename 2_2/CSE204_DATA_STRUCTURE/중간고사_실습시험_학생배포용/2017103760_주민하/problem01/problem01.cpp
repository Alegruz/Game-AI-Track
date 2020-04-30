#include "SortedType.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	srand( time(NULL) );
	SortedType<int> myList;
	size_t listSize = rand() % 10;

	for (size_t item = 0; item < listSize; ++item)
	{
		int itemToAdd = rand() % 10;
		myList.InsertItem(itemToAdd);
	}
	myList.ResetList();
	int itemToPrint;
	for (size_t item = 0; item < listSize; ++item)
	{
		myList.GetNextItem(itemToPrint);
		std::cout << itemToPrint << " ";
	}
	std::cout << std::endl;

	int itemToDelete = rand() % 10;
	std::cout << "Delete " << itemToDelete << std::endl;
	myList.DeleteItem(itemToDelete);

	myList.ResetList();
	for (size_t item = 0; item < myList.LengthIs(); ++item)
	{
		myList.GetNextItem(itemToPrint);
		std::cout << itemToPrint << " ";
	}
	std::cout << std::endl;

	return 0;
}