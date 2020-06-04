#pragma once

#include <new>
#include <cstddef>

#include "NodeType.h"

class FullQueue
{
};

class EmptyQueue
{
};

template <typename ItemType>
class QueType
{
public:
	QueType();
	// Class constructor.
	// Because there is a default constructor, the precondition
	// that the queue has been initialized is omitted.
	QueType(int max);
	// Parameterized class constructor.
	~QueType();
	// Class destructor.
	QueType(const QueType &anotherQue);
	// Copy constructor
	void MakeEmpty();
	// Function: Initializes the queue to an empty state.
	// Post: Queue is empty.
	bool IsEmpty() const;
	// Function: Determines whether the queue is empty.
	// Post: Function value = (queue is empty)
	bool IsFull() const;
	// Function: Determines whether the queue is full.
	// Post: Function value = (queue is full)
	void Enqueue(ItemType newItem);
	// Function: Adds newItem to the rear of the queue.
	// Post: If (queue is full) FullQueue exception is thrown
	//       else newItem is at rear of queue.
	void Dequeue(ItemType &item);
	// Function: Removes front item from the queue and returns it in item.
	// Post: If (queue is empty) EmptyQueue exception is thrown
	//       and item is undefined
	//       else front element has been removed from queue and
	//       item is a copy of removed element.
private:
	NodeType<ItemType>* front;
	NodeType<ItemType>* rear;
};

template <typename ItemType>
QueType<ItemType>::QueType() // Class constructor.
// Post:  front and rear are set to nullptr.
{
	front = nullptr;
	rear = nullptr;
}

template <typename ItemType>
void QueType<ItemType>::MakeEmpty()
// Post: Queue is empty; all elements have been deallocated.
{
	NodeType<ItemType> *tempPtr;

	while (front != nullptr)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = nullptr;
}

// Class destructor.
template <typename ItemType>
QueType<ItemType>::~QueType()
{
	MakeEmpty();
}

template <typename ItemType>
bool QueType<ItemType>::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
	NodeType<ItemType> *location;
	try
	{
		location = new NodeType<ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc)
	{
		return true;
	}
}

template <typename ItemType>
bool QueType<ItemType>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
	return (front == nullptr);
}

template <typename ItemType>
void QueType<ItemType>::Enqueue(ItemType newItem)
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.

{
	if (IsFull())
		throw FullQueue();
	else
	{
		NodeType<ItemType> *newNode;

		newNode = new NodeType<ItemType>;
		newNode->info = newItem;
		newNode->next = nullptr;
		if (rear == nullptr)
			front = newNode;
		else
			rear->next = newNode;
		rear = newNode;
	}
}

template <typename ItemType>
void QueType<ItemType>::Dequeue(ItemType &item)
// Removes front item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the front of the queue has been
//       removed and a copy returned in item;
//       othersiwe a EmptyQueue exception has been thrown.
{
	if (IsEmpty())
		throw EmptyQueue();
	else
	{
		NodeType<ItemType> *tempPtr;

		tempPtr = front;
		item = front->info;
		front = front->next;
		if (front == nullptr)
			rear = nullptr;
		delete tempPtr;
	}
}

template <typename ItemType>
QueType<ItemType>::QueType(const QueType &anotherQue)
{
	NodeType<ItemType>* ptr1;
	NodeType<ItemType>* ptr2;

	if (anotherQue.front == nullptr)
		front = nullptr;
	else
	{
		front = new NodeType<ItemType>;
		front->info = anotherQue.front->info;
		ptr1 = anotherQue.front->next;
		ptr2 = front;
		while (ptr1 != nullptr)
		{
			ptr2->next = new NodeType<ItemType>;
			ptr2 = ptr2->next;
			ptr2->info = ptr1->info;
			ptr1 = ptr1->next;
		}
		ptr2->next = nullptr;
		rear = ptr2;
	}
}
