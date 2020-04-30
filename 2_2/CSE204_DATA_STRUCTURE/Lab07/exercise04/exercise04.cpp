#include "SortedType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	srand( time(NULL) );

	SortedType<int> st;
	size_t listSize = rand() % 10;
	for (size_t node = 0; node < listSize; ++node)
	{
		st.InsertItem(rand() % 10);
	}

	std::cout << st << std::endl;
	st.PrintReverse();

	return 0;
}