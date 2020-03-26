#include "SquareMatrix.h"
#include <iostream>

using namespace Lab01;

int main()
{
	SquareMatrix sqm1(5, 5, 3);
	SquareMatrix sqm2(5, 5, 2);
	SquareMatrix sqm3(5, 5);

	sqm2.Add(sqm1);
	for (size_t rowIndex = 0; rowIndex < 5; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < 5; ++columnIndex)
		{
			std::cout << sqm2[rowIndex][columnIndex] << " ";
		}
		std::cout << std::endl;
	}

	sqm3.Copy(sqm1);
	for (size_t rowIndex = 0; rowIndex < 5; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < 5; ++columnIndex)
		{
			std::cout << sqm1[rowIndex][columnIndex] << " ";
		}
		std::cout << std::endl;
	}

	sqm3.Subtract(sqm2);
	for (size_t rowIndex = 0; rowIndex < 5; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < 5; ++columnIndex)
		{
			std::cout << sqm3[rowIndex][columnIndex] << " ";
		}
		std::cout << std::endl;
	}

	sqm1.MakeEmpty(7);
	for (size_t rowIndex = 0; rowIndex < 5; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < 5; ++columnIndex)
		{
			std::cout << sqm1[rowIndex][columnIndex] << " ";
		}
		std::cout << std::endl;
	}

	sqm2.StoreValue(3, 2, 4);
	for (size_t rowIndex = 0; rowIndex < 5; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < 5; ++columnIndex)
		{
			std::cout << sqm2[rowIndex][columnIndex] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
