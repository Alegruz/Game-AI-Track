#include <chrono>
#include <cmath>
#include <iostream>

double SqrRootRec(double number, double approx, double tol);
double SqrRoot(double number, double approx, double tol);

int main()
{
	auto startTimeRec = std::chrono::high_resolution_clock::now();
	std::cout << SqrRootRec(2., 1., 0.1) << std::endl;
	auto endTimeRec = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTimeRec = endTimeRec - startTimeRec;	
	std::cout << "Elapsed time (Recurrent): " << elapsedTimeRec.count() * 1000 << std::endl;

	auto startTime = std::chrono::high_resolution_clock::now();
	std::cout << SqrRootRec(2., 1., 0.1) << std::endl;
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

double SqrRootRec(double number, double approx, double tol)
{
	if (fabs(approx * approx - number) <= tol)
	{
		return approx;
	}
	else
	{
		return SqrRoot(number, (approx * approx + number) / (2 * approx), tol);
	}
}

double SqrRoot(double number, double approx, double tol)
{
	while (fabs(approx * approx - number) > tol)
	{
		approx = (approx * approx + number) / (2 * approx);
	}

	return approx;
}