#pragma once

#include "Node.h"

#include <new>

template <typename T>
class Stack
{
public:
	Stack();
	virtual ~Stack();

	bool IsEmpty() const;
	bool Push(const T& itemToPush);
	void Pop(T& itemToPop);
	T& Top() const;
private:
	unsigned int mSize;
	Node<T>* mTop;
};

template <typename T>
Stack<T>::Stack()
	: mSize(0), mTop(nullptr)
{
}

template <typename T>
Stack<T>::~Stack()
{
	Node<T>* nodeToDelete;
	while (mTop != nullptr)
	{
		nodeToDelete = mTop;
		mTop = mTop->mNext;
		delete nodeToDelete;
	}
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
	return ( mSize == 0 );
}

template <typename T>
bool Stack<T>::Push(const T& itemToPush)
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

	nodeToAdd->mInfo = itemToPush;
	nodeToAdd->mNext = mTop;

	mTop = nodeToAdd;
	++mSize;

	return true;
}

template <typename T>
void Stack<T>::Pop(T& itemToPop)
{
	if (mSize <= 0)
	{
		return;
	}

	itemToPop = mTop->mInfo;
	Node<T>* nodeToDelete = mTop;
	mTop = mTop->mNext;
	delete nodeToDelete;
	--mSize;
}