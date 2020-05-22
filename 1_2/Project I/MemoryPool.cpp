#include <cstdlib>

#include <iostream>

#include "MemoryPool.h"

namespace neople
{
	MemoryPool::MemoryPool(size_t blockSize, size_t capacity)
		: mBlockSize(blockSize), mMemoryCapacity((capacity % blockSize == 0) ? capacity : capacity + blockSize - capacity % blockSize)
		, mMemory(malloc(capacity)), mFreeSize(0), mAllocatedSize(0)
	{
		if (mMemory != nullptr)
		{
			mMemoryAllocated.reserve(mMemoryCapacity);
			mMemoryFree.reserve(mMemoryCapacity);

			for (size_t i = 0; i < mMemoryCapacity; i += mBlockSize)
			{
				mMemoryFree.push_back(reinterpret_cast<void*>(reinterpret_cast<size_t>(mMemory) + i * (mBlockSize)));
				mMemoryAllocated.push_back(nullptr);
				std::cout << (reinterpret_cast<size_t>(mMemory) + i * (mBlockSize) - reinterpret_cast<size_t>(mMemory)) / mBlockSize << std::endl;
				++mFreeSize;
			}
		}		
	}

	MemoryPool::~MemoryPool()
	{
		free(mMemory);
		mMemoryAllocated.clear();
		mMemoryFree.clear();
	}

	size_t MemoryPool::GetCapacity() const
	{
		return mMemoryCapacity;
	}

	size_t MemoryPool::GetFreeSize() const
	{
		return mFreeSize;
	}

	size_t MemoryPool::GetAllocatedSize() const
	{
		return mAllocatedSize;
	}

	void* MemoryPool::Allocate(size_t memSize)
	{
		if (mMemory == nullptr || memSize <= 0)
		{
			return nullptr;
		}

		if (memSize > mBlockSize || mMemoryFree.empty())
		{
			return malloc(memSize);
		}

		void* newPtr = mMemoryFree.back();
		mMemoryFree.pop_back();
		mMemoryAllocated[(reinterpret_cast<size_t>(newPtr) - reinterpret_cast<size_t>(mMemory)) / mBlockSize] = newPtr;
		++mAllocatedSize;
		--mFreeSize;
	
		return newPtr;
	}
	
	void MemoryPool::Deallocate(void* ptrToDeallocate)
	{
		if (ptrToDeallocate != nullptr && !mMemoryAllocated.empty())
		{
			mMemoryAllocated[(reinterpret_cast<size_t>(ptrToDeallocate) - reinterpret_cast<size_t>(mMemory)) / mBlockSize] = nullptr;
			mMemoryFree[(reinterpret_cast<size_t>(ptrToDeallocate) - reinterpret_cast<size_t>(mMemory)) / mBlockSize] = ptrToDeallocate;
			--mAllocatedSize;
			++mFreeSize;
		}
	}
}