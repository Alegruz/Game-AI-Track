#include "StackType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	srand( time(NULL) );

	StackType* st1 = new StackType;
	size_t stackSize = rand() % 10;
	for (size_t node = 0; node < stackSize; ++node)
	{
		st1->Push(rand() % 10);
	}
	std::cout << *st1 << std::endl;

	StackType st2;
	st2.Copy(*st1);

	std::cout << st2 << std::endl;

	delete st1;

	std::cout << *st1 << std::endl;
	std::cout << st2 << std::endl;

	return 0;
}