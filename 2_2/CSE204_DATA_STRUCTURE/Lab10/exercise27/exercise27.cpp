#include <iostream>
#include "TreeType.h"

int main()
{
	TreeType tt;
	tt.InsertItem('a');
	tt.InsertItem('b');
	tt.InsertItem('z');
	tt.InsertItem('c');
	tt.InsertItem('A');
	tt.InsertItem('d');

	tt.AncestorsRecursive('d');

	return 0;
}