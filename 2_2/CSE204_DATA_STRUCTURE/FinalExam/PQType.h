#pragma once

// Definition of class PQType, which represents the Priority Queue ADT
class FullPQ
{
};

class EmptyPQ
{
};

#include "LLHeapType.h"

class PQType
{
public:
	PQType(int); // parameterized class constructor
	~PQType();	 // class destructor

	void MakeEmpty();
	// Function: Initializes the queue to an empty state.
	// Post: Queue is empty.

	bool IsEmpty() const;
	// Function: Determines whether the queue is empty.
	// Post: Function value = (queue is empty)

	bool IsFull() const;
	// Function: Determines whether the queue is full.
	// Post: Function value = (queue is full)

	void Enqueue(int newItem);
	// Function: Adds newItem to the rear of the queue.
	// Post: if (the priority queue is full) exception FullPQ is thrown;
	//       else newItem is in the queue.

	void Dequeue(int &item);
	// Function: Removes element with highest priority from the queue
	// and returns it in item.
	// Post: If (the priority queue is empty) exception EmptyPQ is thrown;
	//       else highest priority element has been removed from queue.
	//       item is a copy of removed element.

	TreeNode FindParent(int i);
private:
	int mLength;
	LLHeapType mItems;
	int mMaxItems;
};