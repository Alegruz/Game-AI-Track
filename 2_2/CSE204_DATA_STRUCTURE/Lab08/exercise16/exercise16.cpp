#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

double fact(int number);
int NumPathsRec(unsigned int x, unsigned int y, unsigned int gridSize);
int NumPaths(unsigned int x, unsigned int y, unsigned int gridSize);

int main()
{
	auto startTimeRec = std::chrono::high_resolution_clock::now();
	std::cout << NumPathsRec(2, 1, 10) << std::endl;
	auto endTimeRec = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTimeRec = endTimeRec - startTimeRec;	
	std::cout << "Elapsed time (Recurrent): " << elapsedTimeRec.count() * 1000 << std::endl;

	auto startTime = std::chrono::high_resolution_clock::now();
	std::cout << NumPaths(2, 1, 10) << std::endl;
	auto endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTime = endTime - startTime;	
	std::cout << "Elapsed time (Non-Recurrent): " << elapsedTime.count() << std::endl;

	if (elapsedTimeRec.count() > elapsedTime.count())
	{
		std::cout << "Recurrent version without duplicate is better" << std::endl;
	}
	else
	{
		std::cout << "Recurrent version is better" << std::endl;
	}

	return 0;
}

double fact(int number)
{
	int product = 1;
	for (; number > 0; --number)
	{
		product *= number;
	}

	return product;
}

int NumPathsRec(unsigned int x, unsigned int y, unsigned int gridSize)
{
	if (x < 1 || y < 1 || gridSize < 1)
	{
		return -1;
	}

	switch (((x == gridSize) << 1) + (y == gridSize))
	{
	case 0:	return NumPathsRec(x + 1, y, gridSize) + NumPathsRec(x, y + 1, gridSize);
			break;
	case 1:	return NumPathsRec(x + 1, y, gridSize);
			break;
	case 2: return NumPathsRec(x, y + 1, gridSize);
			break;
	case 3: return 1;
			break;
	
	default:
		break;
	}

	return -1;
}

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
				path[x][y - 1] = NumPathsRec(x + 1, y, gridSize);
			}
			if (path[x - 1][y] == 0)
			{
				path[x - 1][y] = NumPathsRec(x, y + 1, gridSize);
			}
			return path[x][y - 1] + path[x - 1][y];
			break;
	case 1:	if (path[x][y - 1] == 0)
			{
				path[x][y - 1] = NumPathsRec(x + 1, y, gridSize);
			}
			return path[x][y - 1];
			break;
	case 2: if (path[x - 1][y] == 0)
			{
				path[x - 1][y] = NumPathsRec(x, y + 1, gridSize);
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