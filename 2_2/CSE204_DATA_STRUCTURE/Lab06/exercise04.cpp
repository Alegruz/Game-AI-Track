#include "UnsortedType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace exercise04;

int main()
{
	srand( time(NULL) );

	UnsortedType<int> ust;

	size_t count = 100;
	while (count-- > 0)
	{
		ust.MakeEmpty();
		size_t listSize = rand() % 10;
		int item;
		for (size_t index = 0; index < listSize; ++index)
		{
			item = rand() % 10;
			ust.InsertItem(item);
		}

		std::cout << ust << std::endl;
		int itemToDelete = rand() % 10;
		std::cout << "Delete " << itemToDelete << std::endl;
		ust.DeleteItem(itemToDelete);
		std::cout << ust << std::endl;
	}

	return 0;
}