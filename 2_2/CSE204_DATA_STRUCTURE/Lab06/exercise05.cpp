#include "SortedType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace exercise05;

int main()
{
	srand( time(NULL) );

	SortedType<int> st;

	size_t count = 100;
	while (count-- > 0)
	{
		st.MakeEmpty();
		size_t listSize = rand() % 10;
		int item;
		for (size_t index = 0; index < listSize; ++index)
		{
			item = rand() % 10;
			st.InsertItem(item);
		}

		std::cout << st << std::endl;
		int itemToDelete = rand() % 10;
		std::cout << "Delete " << itemToDelete << std::endl;
		st.DeleteItem(itemToDelete);
		std::cout << st << std::endl;
	}

	return 0;
}