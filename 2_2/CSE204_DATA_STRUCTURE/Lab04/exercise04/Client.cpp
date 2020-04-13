#include "StackType.h"

#include <iostream>

void ReplaceItem(StackType& stack, const ItemType& oldItem, const ItemType& newItem);

int main()
{
	StackType st;

	st.Push(3);
	st.Push(3);
	st.Push(6);
	st.Push(8);
	st.Push(9);
	std::cout << st << std::endl;

	st.ReplaceItem(3, 6);
	std::cout << st << std::endl;

	st.ReplaceItem(6, 1);
	std::cout << st << std::endl;

	st.ReplaceItem(9, 3);
	std::cout << st << std::endl;

	while (!st.IsEmpty())
	{
		st.Pop();
	}

	st.Push(1);
	st.Push(5);
	st.Push(4);
	st.Push(1);
	st.Push(3);

	// ItemType oldItem = 1;
	// ItemType newItem = 4;
	ReplaceItem(st, 1, 4);
	std::cout << st << std::endl;

	return 0;
}

void ReplaceItem(StackType& stack, const ItemType& oldItem, const ItemType& newItem)
{
	StackType reversalStack;

	while (!stack.IsEmpty())
	{
		int item = stack.Top();
		if (item == oldItem)
		{
			item = newItem;
		}

		reversalStack.Push(item);
		stack.Pop();
	}

	while (!reversalStack.IsEmpty())
	{
		stack.Push(reversalStack.Top());
		reversalStack.Pop();
	}
}