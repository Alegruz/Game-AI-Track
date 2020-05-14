#include "UnsortedType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	srand( time(NULL) );
	
	UnsortedType<int> ust;

	size_t listSize = rand() % 10;
	for (size_t node = 0; node < listSize; ++node)
	{
		ust.InsertItem(rand() % 10);
	}

	std::cout << ust << std::endl;
	
	ust.Sort();

	std::cout << "Sorted" << std::endl;
	std::cout << ust << std::endl;

	return 0;
}