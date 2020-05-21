#include <iostream>

#include "TreeType.h"

int main()
{
	TreeType tt;

	tt.InsertItem('c');
	tt.InsertItem('e');
	tt.InsertItem('a');
	tt.InsertItem('b');
	tt.InsertItem('f');

	tt.ResetTree(PRE_ORDER);
	bool bIsDone = false;
	char item = '\0';
	for (int i = 0; i < tt.LengthIs() && !bIsDone; ++i)
	{
		tt.GetNextItem(item, PRE_ORDER, bIsDone);
		std::cout << item << std::endl;
	}

	std::cout << tt.SingleParentCount() << std::endl;

	return 0;
}