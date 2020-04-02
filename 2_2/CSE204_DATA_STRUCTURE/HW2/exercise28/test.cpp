#include <cassert>
#include <cstdlib>
#include <iostream>

#include "SquareMatrix.h"

using namespace Lab01;

int main()
{
	SquareMatrix sq1;			// Default Initialization        50x50
	SquareMatrix sq2(5);		// Matrix without initial values 5x5
	SquareMatrix sq3(4, 5);		// Matrix with initial values    4x5

	std::cerr << "TEST CASE 01 CONSTRUCTOR: ";
	{
		// Default Initialization
		for (size_t row = 0; row < 50; ++row)
		{
			assert(sq1[row] != nullptr);
		}

		for (size_t row = 0; row < 5; ++row)
		{
			for (size_t column = 0; column < 5; ++column)
			{
				assert(sq2[row] != nullptr);
			}
		}

		for (size_t row = 0; row < 4; ++row)
		{
			for (size_t column = 0; column < 4; ++column)
			{
				assert(sq3[row][column] == 5);
			}
		}
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "TEST CAST 02 MakeEmpty: ";
	{
		sq1.MakeEmpty();
		for (size_t row = 0; row < 50; ++row)
		{
			for (size_t column = 0; column < 50; ++column)
			{
				assert(sq1[row][column] == 0);
			}
		}

		sq2.MakeEmpty();
		for (size_t row = 0; row < 5; ++row)
		{
			for (size_t column = 0; column < 5; ++column)
			{
				assert(sq2[row][column] == 0);
			}
		}


		sq3.MakeEmpty();
		for (size_t row = 0; row < 4; ++row)
		{
			for (size_t column = 0; column < 4; ++column)
			{
				assert(sq3[row][column] == 0);
			}
		}
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "TEST CASE 03 StoreValue: ";
	{
		sq1.MakeEmpty();
		sq2.MakeEmpty();
		sq3.MakeEmpty();

		sq1.StoreValue(20, 30, 100);
		for(size_t row = 0; row < 50; ++row)
		{
			for (size_t column = 0; column < 50; ++column)
			{
				if (row == 20 && column == 30)
				{
					assert(sq1[row][column] == 100);
					continue;
				}
				assert(sq1[row][column] == 0);
			}
		}

		sq2.StoreValue(40, 0, 100);
		for(size_t row = 0; row < 5; ++row)
		{
			for (size_t column = 0; column < 5; ++column)
			{
				assert(sq2[row][column] == 0);
			}
		}

		sq3.StoreValue(2, 2, 100);
		for(size_t row = 0; row < 4; ++row)
		{
			for (size_t column = 0; column < 4; ++column)
			{
				if (row == 2 && column == 2)
				{
					assert(sq3[row][column] == 100);
					continue;
				}
				assert(sq3[row][column] == 0);
			}
		}
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "TEST CASE 04 Add: ";
	{
		SquareMatrix sq7(10, 50);
		SquareMatrix sq8(10, 30);
		sq7.Add(sq8);

		for(size_t row = 0; row < 10; ++row)
		{
			for (size_t column = 0; column < 10; ++column)
			{
				assert(sq7[row][column] == 80);
			}
		}

		SquareMatrix sq9(5, 20);
		sq8.Add(sq9);

		for(size_t row = 0; row < 5; ++row)
		{
			for (size_t columnAdded = 0; columnAdded < 5; ++columnAdded)
			{
				assert(sq8[row][columnAdded] == 50);
			}
			for (size_t columnNotAdded = 5; columnNotAdded < 10; ++columnNotAdded)
			{
				assert(sq8[row][columnNotAdded] == 30);
			}
		}
		for(size_t row = 5; row < 10; ++row)
		{
			for (size_t column = 0; column < 10; ++column)
			{
				assert(sq8[row][column] == 30);
			}
		}

		SquareMatrix sq10(20, -20);
		sq9.Add(sq10);

		for(size_t row = 0; row < 5; ++row)
		{
			for (size_t column = 0; column < 5; ++column)
			{
				assert(sq9[row][column] == 0);
			}
		}
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "TEST CASE 05 Subtract: ";
	{
		SquareMatrix sq7(10, 50);
		SquareMatrix sq8(10, 30);
		sq7.Subtract(sq8);

		for(size_t row = 0; row < 10; ++row)
		{
			for (size_t column = 0; column < 10; ++column)
			{
				assert(sq7[row][column] == 20);
			}
		}

		SquareMatrix sq9(5, 20);
		sq8.Subtract(sq9);

		for(size_t row = 0; row < 5; ++row)
		{
			for (size_t columnAdded = 0; columnAdded < 5; ++columnAdded)
			{
				assert(sq8[row][columnAdded] == 10);
			}
			for (size_t columnNotAdded = 5; columnNotAdded < 10; ++columnNotAdded)
			{
				assert(sq8[row][columnNotAdded] == 30);
			}
		}
		for(size_t row = 5; row < 10; ++row)
		{
			for (size_t column = 0; column < 10; ++column)
			{
				assert(sq8[row][column] == 30);
			}
		}

		SquareMatrix sq10(5, -20);
		sq9.Subtract(sq10);

		for(size_t row = 0; row < 5; ++row)
		{
			for (size_t column = 0; column < 5; ++column)
			{
				assert(sq9[row][column] == 40);
			}
		}
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << "TEST CASE 06 Copy: ";
	{
		SquareMatrix* sq7 = new SquareMatrix(5, 1);
		SquareMatrix sq8(6, 4);
		sq7->Copy(sq8);
		assert(reinterpret_cast<uintptr_t>(sq7) != reinterpret_cast<uintptr_t>(&sq8));
		for (size_t row = 0; row < 6; ++row)
		{
			for (size_t column = 0; column < 6; ++column)
			{
				assert((*sq7)[row][column] == 4);
				assert(sq8[row][column] == 4);
			}
		}
	}
	std::cerr << "SUCCESS" << std::endl;

	return 0;
}