#include <iostream>

#include "QuickSort.h"
#include "Student.h"

int main()
{
	Student stu[100];
	stu[0].InitValue(2003200111, "이웅재", 3.0);
	stu[1].InitValue(2004200121, "권오준", 3.2);
	stu[2].InitValue(2005200132, "김진일", 2.7);

	QuickSort(stu, 0, 2);
	Print(cout, stu, 3);
	return 0;
}