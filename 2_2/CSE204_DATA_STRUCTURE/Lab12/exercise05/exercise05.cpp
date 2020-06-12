#include <iostream>

#include "HeapSort.h"

int main()
{
	int arr[] = {25, 17, 36, 2, 3, 100, 1, 19, 7};

	HeapSort(arr, 9);
	
	Print(arr, 9);
	return 0;
}