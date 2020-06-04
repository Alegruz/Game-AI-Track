#include <cstddef> // For nullptr
#include <new>	   // For bad_alloc
#include "QueType.h"

QueType::QueType() // Class constructor.
// Post:  front and rear are set to nullptr.
{
	front = nullptr;
	rear = nullptr;
}

void QueType::MakeEmpty()
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
QueType::~QueType()
{
	MakeEmpty();
}

bool QueType::IsFull() const
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

bool QueType::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
	return (front == nullptr);
}

void QueType::Enqueue(ItemType newItem)
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

void QueType::Dequeue(ItemType &item)
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

QueType::QueType(const QueType &anotherQue)
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
