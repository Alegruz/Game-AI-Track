#include "UnsortedList.h"
#include "SortedList.h"

#include <cassert>
#include <iostream>

int main()
{
	UnsortedList<int> ul1;
	UnsortedList<int> ul2(5);
	UnsortedList<int> ul3(ul2);
	UnsortedList<int> ul4 = ul2;
	SortedList<int> l1;
	SortedList<int> l2(5);
	SortedList<int> l3;

	// Constructor
	assert( ul1.Size() == 0 );
	assert( ul1.Capacity() == 8 );
	assert( ul2.Size() == 0 );
	assert( ul2.Capacity() == 5 );
	assert( ul3.Size() == 0 );
	assert( ul3.Capacity() == 5 );
	assert( ul4.Size() == 0 );
	assert( ul4.Capacity() == 5 );
	ul4 = ul4;
	assert( ul4.Size() == 0 );
	assert( ul4.Capacity() == 5 );
	ul4 = ul1;
	assert( ul4.Size() == 0 );
	assert( ul4.Capacity() == 8 );


	return 0;
}