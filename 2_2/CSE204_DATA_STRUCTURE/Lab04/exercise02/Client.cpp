#include "StackTType.h"

#include <iostream>

template <typename T>
StackType<T> CopyStack(const StackType<T>& other);

int main()
{
	StackType<int> stack;

	for (int number = 1; number <= 5; ++number)
	{
		stack.Push(number);
	}

	StackType<int> newStack = CopyStack(stack);

	for (int number = 1; number <= 5; ++number)
	{
		std::cout << stack.Top() << " " << newStack.Top() << std::endl;;
		stack.Pop();
		newStack.Pop();
	}


	return 0;
}

template <typename T>
StackType<T> CopyStack(const StackType<T>& other)
{
	StackType<T> newStack;

	if (other.IsEmpty())
	{
		return newStack;
	}

	StackType<T> copyOther = other;
	StackType<T> tempStack;
	while (!copyOther.IsEmpty())
	{
		tempStack.Push(copyOther.Top());
		copyOther.Pop();
	}

	while (!tempStack.IsEmpty())
	{
		newStack.Push(tempStack.Top());
		tempStack.Pop();
	}

	return newStack;
}