#include <vector>
// a
// int NumPaths(int row, int col, int n)
// {
// 	if (row == n)
// 		return 1;
// 	else
// 		if (col == n)
// 			return NumPaths + 1;	// returning function pointer to an int function
// 		else
// 			return NumPaths(row + 1, col) * NumPaths(row, col + 1);	// needs 3 arguments, not 2. needs to return the sum, not the product
// }

// b
int NumPaths(int row, int col, int n)
{
	if (row == n)
		return 1;
	else
		if (col == n)
			return 1;
		else
			return NumPaths(row + 1, col, n) + NumPaths(row, col + 1, n);
}

// NumPaths(1, 1, 4)
// NumPaths(2, 1, 4) + NumPaths(1, 2, 4)
// (NumPaths(3, 1, 4) + NumPaths(2, 2, 4)) + (NumPaths(2, 2, 4) + NumPaths(2, 3, 4))
// ((NumPaths(4, 1, 4) + NumPaths(3, 2, 4)) + (NumPaths(3, 2, 4) + NumPaths(2, 3, 4))) + ((NumPaths(3, 2, 4) + NumPaths(2, 3, 4)) + (NumPaths(3, 3, 4) + NumPaths(2, 4, 4)))
// ((1 + (NumPaths(4, 2, 4) + NumPaths(3, 3, 4))) + ((NumPaths(4, 2, 4) + NumPaths(3, 3, 4)) + (NumPaths(3, 3, 4) + NumPaths(2, 4, 4)))) + (((NumPaths(4, 2, 4) + NumPaths(3, 3, 4)) + (NumPaths(3, 3, 4) + NumPaths(2, 4, 4))) + ((NumPaths(4, 2, 4) + NumPaths(3, 3, 4)) + 1))
// ((1 + (1 + (NumPaths(4, 3, 4) + NumPaths(3, 4, 4)))) + ((1 + (NumPaths(4, 3, 4) + NumPaths(3, 4, 4))) + ((NumPaths(4, 3, 4) + NumPaths(3, 4, 4)) + 1))) + (((1 + (NumPaths(4, 3, 4) + NumPaths(3, 4, 4))) + ((NumPaths(4, 3, 4) + NumPaths(3, 4, 4)) + 1)) + ((1 + (NumPaths(4, 3, 4) + NumPaths(3, 4, 4))) + 1))
// 20

// c
int NumPaths(unsigned int x, unsigned int y, unsigned int gridSize)
{
	static std::vector<std::vector<int>> path(gridSize, std::vector<int>(gridSize));

	if (x < 1 || y < 1 || gridSize < 1)
	{
		return -1;
	}

	switch (((x == gridSize) << 1) + (y == gridSize))
	{
	case 0:	if (path[x][y - 1] == 0)
			{
				path[x][y - 1] = NumPaths(x + 1, y, gridSize);
			}
			if (path[x - 1][y] == 0)
			{
				path[x - 1][y] = NumPaths(x, y + 1, gridSize);
			}
			return path[x][y - 1] + path[x - 1][y];
			break;
	case 1:	if (path[x][y - 1] == 0)
			{
				path[x][y - 1] = NumPaths(x + 1, y, gridSize);
			}
			return path[x][y - 1];
			break;
	case 2: if (path[x - 1][y] == 0)
			{
				path[x - 1][y] = NumPaths(x, y + 1, gridSize);
			}
			return path[x - 1][y];
			break;
	case 3: path[x - 1][y - 1] = 1;
			return 1;
			break;
	
	default:
		break;
	}

	return -1;
}

// d
/*
 1. a static 2-dimensional, gridSize x gridSize vector is initialized with 0
 2. based on current position (x, y), check whether it is located at the border or at the middle, or at the end.
 3. based on its position, check whether the vector's element at next two positions are 0
 4. if 0, then initialize it with its position, if not, then simply fetch the result(s) and return 
 5. repeat until x, y reaches the end
 */

// e
/*
 Time-wise, version c: O(n), version b: O(n^2)
 Space-wise, version c: O(n), version b: O(n)
 */