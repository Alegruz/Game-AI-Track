#include <iostream>

#include "SortedType.h"
#include "TreeType.h"

void AddItem(TreeType& tree, int* items, size_t front, size_t rear);
void MakeTree(TreeType& tree, SortedType<int>& intList);

int main()
{
	TreeType tt;
	SortedType<int> intList;
	for (int i = 1; i < 8; ++i)
	{
		intList.InsertItem(i);
	}

	std::cout << intList << std::endl;

	MakeTree(tt, intList);

	tt.ResetTree(PRE_ORDER);

	ItemType itemToPrint;
	bool bIsFinished = false;
	for (int i = 0; i < tt.LengthIs() && !bIsFinished; ++i)
	{
		tt.GetNextItem(itemToPrint, PRE_ORDER, bIsFinished);
		std::cout << "[" << i << "]: " << itemToPrint << std::endl;
	}

	return 0;
}

void AddItem(TreeType& tree, int* items, int front, int rear)
{
	if (front <= rear)
	{
		int mid = (front + rear) / 2;

		tree.InsertItem(items[mid]);
		AddItem(tree, items, front, mid - 1);
		AddItem(tree, items, mid + 1, rear);
	}
}

void MakeTree(TreeType& tree, SortedType<int>& intList)
{
	intList.ResetList();

	int items[intList.LengthIs()];
	int item;
	for (size_t i = 0; i < static_cast<size_t>(intList.LengthIs()); ++i)
	{
		intList.GetNextItem(item);
		items[i] = item;
	}

	int front = 0;
	int rear = intList.LengthIs() - 1;

	AddItem(tree, items, front, rear);
}