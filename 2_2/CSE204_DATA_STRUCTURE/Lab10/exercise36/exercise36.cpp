#include <iostream>
#include "TreeType.h"
#include "UnsortedType.h"

void AddItem(TreeType& tree, int* items, size_t front, size_t rear);
void MakeTree(TreeType& tree, UnsortedType<int>& intList);
bool MatchingItem(TreeType& tree, UnsortedType<int>& list);

int main()
{
	TreeType tt;
	UnsortedType<int> intList;
	for (int i = 1; i < 8; ++i)
	{
		intList.InsertItem(i);
	}

	UnsortedType<int> intList1;
	for (int i = 1; i < 7; ++i)
	{
		intList1.InsertItem(i);
	}

	UnsortedType<int> intList2;
	for (int i = 1; i < 8; ++i)
	{
		intList2.InsertItem(i * 2);
	}

	MakeTree(tt, intList);

	tt.ResetTree(PRE_ORDER);

	ItemType itemToPrint;
	bool bIsFinished = false;
	for (int i = 0; i < tt.LengthIs() && !bIsFinished; ++i)
	{
		tt.GetNextItem(itemToPrint, PRE_ORDER, bIsFinished);
		std::cout << "[" << i << "]: " << itemToPrint << std::endl;
	}

	std::cout << std::boolalpha << MatchingItem(tt, intList) << std::endl;
	std::cout << std::boolalpha << MatchingItem(tt, intList1) << std::endl;
	std::cout << std::boolalpha << MatchingItem(tt, intList2) << std::endl;

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

void MakeTree(TreeType& tree, UnsortedType<int>& intList)
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

bool MatchingItem(TreeType& tree, UnsortedType<int>& list)
{
	if (tree.LengthIs() == list.LengthIs())
	{
		bool bHasItem = true;
		int itemToSearch;
		list.ResetList();
		for (int i = 0; i < tree.LengthIs() && bHasItem; ++i)
		{
			list.GetNextItem(itemToSearch);
			tree.RetrieveItem(itemToSearch, bHasItem);
		}

		return bHasItem;
	}

	return false;
}