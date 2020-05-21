#include <cassert>
#include <iostream>

#include "TreeType.h"

int main()
{
	TreeType tt;

	tt.InsertItem('b');
	tt.InsertItem('c');
	tt.InsertItem('a');

	tt.ResetTree(PRE_ORDER);
	bool bIsDone = false;
	char item = '\0';
	for (int i = 0; i < tt.LengthIs() && !bIsDone; ++i)
	{
		tt.GetNextItem(item, PRE_ORDER, bIsDone);
		std::cout << item << std::endl;
	}

	TreeNode tn4 = {'a'-1, nullptr, nullptr};
	TreeNode tn3 = {'d', nullptr, nullptr};
	TreeNode tn2 = {'a', &tn4, nullptr};
	TreeNode tn1 = {'c', nullptr, &tn3};
	TreeNode* rn = new TreeNode({'b', &tn2, &tn1});
	TreeNode* newTn = new TreeNode({'\0', nullptr, nullptr});
	newTn = tt.PtrToSuccessorRecursive(rn);

	assert(newTn == &tn4);
	assert(tn2.left == nullptr);

	return 0;
}