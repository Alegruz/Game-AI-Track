#include <chrono>
#include <iostream>
#include <vector>

int FibonacciRec(int index);
int Fibonacci(int index);

int main()
{
	auto startTimeRec = std::chrono::high_resolution_clock::now();

	std::cout << "F[10]: " << FibonacciRec(10) << std::endl;		// Time Complexity:  O(n) > memoization
																	// Space Complexity: O(n) > calling FibonacciRec n times

	auto endTimeRec = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTimeRec = endTimeRec - startTimeRec;	
	std::cout << "Elapsed time (Recurrent): " << elapsedTimeRec.count() * 1000 << std::endl;

	auto startTime = std::chrono::high_resolution_clock::now();

	std::cout << "F[10]: " << Fibonacci(10) << std::endl;			// Time Complexity:  O(n) > while statement
																	// Space Complexity: O(1) > single function call

	auto endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTime = endTime - startTime;	
	std::cout << "Elapsed time (Non-Recurrent): " << elapsedTime.count() << std::endl;

	if (elapsedTimeRec.count() > elapsedTime.count())
	{
		std::cout << "Non recurrent version is better" << std::endl;
	}
	else
	{
		std::cout << "Recurrent version is better" << std::endl;
	}
	

	return 0;
}

int FibonacciRec(int index)
{
	static std::vector<int> fibArr(index, -1);

	if (index < 0)
	{
		return -1;
	}

	if (index <= 1)
	{
		fibArr[index] = index;
		return index;
	}

	if (fibArr[index - 2] == -1)
	{
		fibArr[index - 2] = FibonacciRec(index - 2);
	}
	if (fibArr[index - 1] == -1)
	{
		fibArr[index - 1] = FibonacciRec(index - 1);
	}

	return fibArr[index - 2] + fibArr[index - 1];
}

int Fibonacci(int index)
{
	if (index < 0)
	{
		return -1;
	}

	if (index <= 1)
	{
		return index;
	}

	int fib0 = 0;
	int fib1 = 1;
	int tempFib;
	while (index > 1)
	{
		tempFib = fib1;
		fib1 = fib0 + fib1;
		fib0 = tempFib;

		--index;
	}

	return fib1;
}