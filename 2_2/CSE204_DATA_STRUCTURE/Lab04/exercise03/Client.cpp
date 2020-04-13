#include "DoubleStack.h"

#include <iostream>

int main()
{
	DoubleStack ds;

	for (int number = 1; number <= 10; ++number)
	{
		ds.Push(number);
	}

	for (int number = 1001; number <= 1011; ++number)
	{
		ds.Push(number);
	}

	std::cout << ds << std::endl;

	for (int number = 1; number <= 5; ++number)
	{
		std::cout << "Popping " << ds.PopBelowEqualKey() << std::endl;
	}

	for (int number = 1; number <= 5; ++number)
	{
		std::cout << "Popping " << ds.PopAboveKey() << std::endl;
	}

	std::cout << ds << std::endl;

	return 0;
}