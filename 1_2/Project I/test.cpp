#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "MemoryPool.h"

int main()
{
	srand(time(NULL));
	size_t memoryPoolSize = (rand() % 1000 + 1) * 10;
	auto startTimeRec = std::chrono::high_resolution_clock::now();
	neople::MemoryPool mp(4, memoryPoolSize);
	auto endTimeRec = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTimeRec = endTimeRec - startTimeRec;
	std::cout << "Memory Pool of Size " << memoryPoolSize << " Initialized by 4 bytes: " << elapsedTimeRec.count() * 1000 << std::endl;
	std::cout << "Capacity: " << mp.GetCapacity() << " Free: " << mp.GetFreeSize() << " Allocated: " << mp.GetAllocatedSize() << std::endl;

	startTimeRec = std::chrono::high_resolution_clock::now();
	int* intPtrListByMemPool[memoryPoolSize / 4];
	for (size_t i = 0; i < memoryPoolSize / 4; ++i)
	{
		intPtrListByMemPool[i] = static_cast<int*>(mp.Allocate(4));
	}
	endTimeRec = std::chrono::high_resolution_clock::now();

	elapsedTimeRec = endTimeRec - startTimeRec;
	std::cout << "Variable Initialization by MemPool: " << elapsedTimeRec.count() * 1000 << std::endl;
	// std::cout << "Capacity: " << mp.GetCapacity() << " Free: " << mp.GetFreeSize() << " Allocated: " << mp.GetAllocatedSize() << std::endl;

	startTimeRec = std::chrono::high_resolution_clock::now();
	int* intPtrListByNew[memoryPoolSize / 4];
	for (size_t i = 0; i < memoryPoolSize / 4; ++i)
	{
		intPtrListByNew[i] = new int();
	}
	endTimeRec = std::chrono::high_resolution_clock::now();

	elapsedTimeRec = endTimeRec - startTimeRec;
	std::cout << "Variable Initialization by new: " << elapsedTimeRec.count() * 1000 << std::endl;

	startTimeRec = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < memoryPoolSize / 4; ++i)
	{
		mp.Deallocate(intPtrListByMemPool[i]);
	}
	endTimeRec = std::chrono::high_resolution_clock::now();

	elapsedTimeRec = endTimeRec - startTimeRec;
	std::cout << "Variable Deletion by MemPool: " << elapsedTimeRec.count() * 1000 << std::endl;
	// std::cout << "Capacity: " << mp.GetCapacity() << " Free: " << mp.GetFreeSize() << " Allocated: " << mp.GetAllocatedSize() << std::endl;

	startTimeRec = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < memoryPoolSize / 4; ++i)
	{
		mp.Deallocate(intPtrListByNew[i]);
	}
	endTimeRec = std::chrono::high_resolution_clock::now();

	elapsedTimeRec = endTimeRec - startTimeRec;
	std::cout << "Variable Deletion by delete: " << elapsedTimeRec.count() * 1000 << std::endl;
	return 0;
}