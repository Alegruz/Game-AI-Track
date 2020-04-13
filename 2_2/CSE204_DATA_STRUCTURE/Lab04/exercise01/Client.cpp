#include "StackTType.h"

#include <iostream>

int main()
{
	StackType<int> stack;

	for (int number = 1; number <= 6; ++number)
	{
		stack.Push(number);
	}

	while (!stack.IsEmpty())
	{
		std::cout << "Top is: " << stack.Top() << std::endl;
		stack.Pop();
	}


	return 0;
}