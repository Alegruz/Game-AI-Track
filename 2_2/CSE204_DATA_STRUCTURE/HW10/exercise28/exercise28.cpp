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

	tt.Ancestors('B');

	return 0;
}