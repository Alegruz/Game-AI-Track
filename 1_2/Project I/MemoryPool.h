#pragma once

#include <vector>

namespace neople
{
	class MemoryPool
	{
	public:
		MemoryPool(size_t blockSize, size_t capacity);
		~MemoryPool();

		size_t GetCapacity() const;
		size_t GetFreeSize() const;
		size_t GetAllocatedSize() const;
		void* Allocate(size_t memSize);
		void Deallocate(void* ptrToDeallocate);
	private:
		size_t mBlockSize;
		size_t mMemoryCapacity;
		void* mMemory;
		size_t mAllocatedSize;
		size_t mFreeSize;
		std::vector<void*> mMemoryAllocated;
		std::vector<void*> mMemoryFree;
	};
}