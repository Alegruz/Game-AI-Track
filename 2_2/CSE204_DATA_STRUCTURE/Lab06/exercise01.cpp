#include "StackType.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace exercise01;

void ReplaceItem(StackType& stack, const ItemType& oldItem, const ItemType& newItem);

int main()
{
	srand ( time(NULL) );

	StackType st1;
	size_t stackSize1 = rand() % 10;
	ItemType item;
	for (size_t index = 0; index < stackSize1; ++index)
	{
		item = rand() % 10;
		st1.Push(item);
	}
	std::cout << st1 << std::endl;
	ReplaceItem(st1, 3, 3000);
	std::cout << st1 << std::endl;
	st1.ReplaceItem(4, 4000);
	std::cout << st1 << std::endl;
	
	return 0;
}

void ReplaceItem(StackType& stack, const ItemType& oldItem, const ItemType& newItem)
{
	if (stack.IsEmpty())
	{
		return;
	}

	StackType tempStack;
	ItemType item;
	while (!stack.IsEmpty())
	{
		item = stack.Top();
		stack.Pop();
		if (item == oldItem)
		{
			item = newItem;
		}
		tempStack.Push(item);
	}

	while (!tempStack.IsEmpty())
	{
		item = tempStack.Top();
		tempStack.Pop();
		stack.Push(item);
	}
}