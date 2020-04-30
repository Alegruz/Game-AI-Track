#pragma once

#include "Node.h"

#include <new>

template <typename T>
class Queue
{
public:
	Queue();
	virtual ~Queue();

	bool IsEmpty() const;
	bool Enqueue(const T& itemToAdd);
	void Dequeue(T& itemToRemove);
private:
	unsigned int mSize;
	Node<T>* mFront;
	Node<T>* mRear;
};

template <typename T>
Queue<T>::Queue()
	: mSize(0), mFront(nullptr), mRear(nullptr)
{
}

template <typename T>
Queue<T>::~Queue()
{
	Node<T>* nodeToDelete;
	while (mFront != nullptr)
	{
		nodeToDelete = mFront;
		mFront = mFront->mNext;
		delete nodeToDelete;
	}

	mRear = nullptr;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
	return ( mSize == 0 );
}

template <typename T>
bool Queue<T>::Enqueue(const T& itemToAdd)
{
	Node<T>* nodeToAdd;
	try
	{
		nodeToAdd = new Node<T>;
	}
	catch(std::bad_alloc exception)
	{
		return false;
	}

	nodeToAdd->mInfo = itemToAdd;
	nodeToAdd->mNext = nullptr;

	if (mRear != nullptr)
	{
		mRear->mNext = nodeToAdd;
	}

	mRear = nodeToAdd;

	if (mFront == nullptr)
	{
		mFront = nodeToAdd;
	}

	++mSize;
	return true;
}

template <typename T>
void Queue<T>::Dequeue(T& itemToRemove)
{
	if (mSize <= 0)
	{
		return;
	}

	itemToRemove = mFront->mInfo;
	Node<T>* nodeToDelete = mFront;
	mFront = mFront->mNext;
	delete nodeToDelete;
	--mSize;
}