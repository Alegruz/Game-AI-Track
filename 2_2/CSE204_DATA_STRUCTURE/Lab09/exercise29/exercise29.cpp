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

	std::cout << std::boolalpha << tt.IsBST() << std::endl;

	return 0;
}