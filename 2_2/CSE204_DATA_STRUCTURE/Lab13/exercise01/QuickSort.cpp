#include <cstring>
#include "QuickSort.h"

void Split(Student values[], int first, int last, int& splitPoint)
{
	Student splitVal = values[first];
	int saveFirst = first;
	bool onCorrectSide;

	first++;
	do
	{
		onCorrectSide = true;
		while (onCorrectSide)         // Move first toward last.
		{
			if (strcmp(values[first].getName(), splitVal.getName()) > 0)
			{
				onCorrectSide = false;
			}
			else
			{  
				first++;
				onCorrectSide = (first <= last);
			}
		}

		onCorrectSide = (first <= last);
		while (onCorrectSide)             // Move last toward first.
		{
			if (strcmp(values[last].getName(), splitVal.getName()) <= 0)
			{
				onCorrectSide = false;
			}
			else
			{
				last--;
				onCorrectSide = (first <= last);
			}
		}

		if (first < last)
		{
			Swap(values[first], values[last]);
			first++;
			last--;
		}
	} while (first <= last);

	splitPoint = last;
	Swap(values[saveFirst], values[splitPoint]);
}

void QuickSort(Student values[], int first, int last)
{
	if (first < last)
	{
		int splitPoint;

		Split(values, first, last, splitPoint);
		// values[first]..values[splitPoint-1] <= splitVal
		// values[splitPoint] = splitVal
		// values[splitPoint+1]..values[last] > splitVal

		QuickSort(values, first, splitPoint-1);
		QuickSort(values, splitPoint+1, last);
	}
}