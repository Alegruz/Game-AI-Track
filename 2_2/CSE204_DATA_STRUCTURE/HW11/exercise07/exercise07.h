/*
 A priority queue is implemented as a sequential array-based list.
 The highest-priority item is in the first array position,
 the second-highest priority item is in the second array position,
 and so on.
 
 a. Write the declarations in the private part of the priority queue class definition needed for this implementation.
 */

#include <cassert>
#include <cstddef>

template <typename T>
class PriorityQueue
{
public:
	void Enqueue(const T& item);
	T Dequeue();
private:
	size_t mCapacity;
	size_t mSize;
	T* mQueue;
};

/*
 b .Write the Enqueue operation, using this implementation.
 */

template <typename T>
void PriorityQueue<T>::Enqueue(const T& item)
{
	if (mSize >= mCapacity)
	{
		T* tempQueue = new T[mSize];

		for (size_t itemToAdd = 0; itemToAdd < mSize; ++itemToAdd)
		{
			tempQueue[itemToAdd] = mQueue[itemToAdd];
		}

		delete[] mQueue;

		mCapacity *= 2;
		mQueue = new T[mCapacity];

		for (size_t itemToAdd = 0; itemToAdd < mSize; ++itemToAdd)
		{
			mQueue[itemToAdd] = tempQueue[itemToAdd];
		}
	}

	size_t head = 0;
	size_t tail = mSize - 1;
	size_t middle;
	
	do
	{
		middle = (head + mSize) / 2;
		if (mQueue[middle] < item)
		{
			tail = middle - 1;
		}
		else if (mQueue[middle] > item)
		{
			head = middle + 1;
		}
		else
		{
			break;
		}
	} while (head <= tail);
	
	for (size_t i = mSize; i > middle; --i)
	{
		mQueue[i] = mQueue[i - 1];
	}
	mQueue[middle] = item;

	++mSize;
}


/*
 c.Write the Dequeue operation, using this implementation.
 */

template <typename T>
T PriorityQueue<T>::Dequeue()
{
	assert(mSize > 0);
	--mSize;
	return mQueue[mSize];
}

/*
 d.Compare the Enqueue and Dequeue operations to those for the heap implementation, in terms of Big-O notation.
 Under what conditions would this implementation be better or worse than the heap implementation?

 Enqueue: O(log_2(n)) (reset memory) + (binary search) + (insertion)
 Dequeue: O(1)

 Heap
 Enqueue: O(log_2(n))
 Dequeue: O(log_2(n))

 */