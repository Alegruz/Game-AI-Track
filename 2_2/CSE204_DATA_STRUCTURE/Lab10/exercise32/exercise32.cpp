#include <iostream>
#include "TreeType.h"

size_t Smaller(TreeType& tree, const ItemType& item);

int main()
{
	TreeType tt;
	tt.InsertItem('a');
	tt.InsertItem('b');
	tt.InsertItem('z');
	tt.InsertItem('c');
	tt.InsertItem('B');
	tt.InsertItem('d');
	tt.InsertItem('A');
	tt.InsertItem('C');
	tt.InsertItem('z' + 1);

	tt.ResetTree(PRE_ORDER);
	ItemType itemToPrint;
	bool bIsFinished = false;
	for (int i = 0; i < tt.LengthIs() && !bIsFinished; ++i)
	{
		tt.GetNextItem(itemToPrint, PRE_ORDER, bIsFinished);
		std::cout << "[" << i << "]: " << itemToPrint << std::endl;
	}

	ItemType itemThreshold = 'z';
	std::cout << "Number of items smaller than " << itemThreshold << " is " << Smaller(tt, itemThreshold) << std::endl;

	return 0;
}

size_t Smaller(TreeType& tree, const ItemType& item)
{
	tree.ResetTree(IN_ORDER);

	size_t smallerItemCount = 0;
	bool bFound = false;
	ItemType itemToSearch;
	while (!bFound)
	{
		tree.GetNextItem(itemToSearch, IN_ORDER, bFound);
		if (itemToSearch < item)
		{
			++smallerItemCount;
		}
		else
		{
			break;
		}
	}

	return smallerItemCount;
}