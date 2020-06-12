/*
 c. The precedence / relation used for binary search is merely a promise between users.
 If new tree insists to have bigger element on the left side and smaller to be on the right side, then so be it.
 Only procedure needs to be taken is to reverse the way we use the binary search from left to right to right to left.

	BEFORE:
	if (tree == NULL)
		found = false;                     // item is not found.
	else if (item < tree->info)      
		Retrieve(tree->left, item, found); // Search left subtree.
	else if (item > tree->info)
		Retrieve(tree->right, item, found);// Search right subtree.
	else
	{
		item = tree->info;                 // item is found.
		found = true;
	}

	AFTER:
	if (tree == NULL)
		found = false;                     // item is not found.
	else if (item > tree->info)      
		Retrieve(tree->left, item, found); // Search left subtree.
	else if (item < tree->info)
		Retrieve(tree->right, item, found);// Search right subtree.
	else
	{
		item = tree->info;                 // item is found.
		found = true;
	}
 */

#include <iostream>
#include "TreeType.h"

int main()
{
	TreeType tt;
	tt.InsertItem('Q');
	tt.InsertItem('K');
	tt.InsertItem('D');
	tt.InsertItem('B');
	tt.InsertItem('J');
	tt.InsertItem('M');
	tt.InsertItem('P');
	tt.InsertItem('N');
	tt.InsertItem('T');
	tt.InsertItem('R');
	tt.InsertItem('Y');
	tt.InsertItem('W');

	TreeType ttt;
	tt.MirrorImage(ttt);

	tt.ResetTree(IN_ORDER);
	bool bIsDone = false;
	int item = 0;
	while (!bIsDone)
	{
		tt.GetNextItem(item, IN_ORDER, bIsDone);
		std::cout << static_cast<char>(item) << std::endl;
	}

	std::cout << std::endl;

	ttt.ResetTree(IN_ORDER);
	bIsDone = false;
	item = 0;
	while (!bIsDone)
	{
		ttt.GetNextItem(item, IN_ORDER, bIsDone);
		std::cout << static_cast<char>(item) << std::endl;
	}

	return 0;
}