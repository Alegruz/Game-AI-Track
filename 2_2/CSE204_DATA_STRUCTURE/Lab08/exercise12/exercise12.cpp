#include "UnsortedType.h"

#include <iostream>

int main()
{
	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	int item4 = 4;
	int item5 = 5;

	UnsortedType<int> ust;

	ust.InsertItem(item1);
	ust.InsertItem(item2);
	ust.InsertItem(item3);
	ust.InsertItem(item4);
	ust.InsertItem(item5);

	std::cout << ust << std::endl;
	ust.PrintSumSquare();

	return 0;
}
