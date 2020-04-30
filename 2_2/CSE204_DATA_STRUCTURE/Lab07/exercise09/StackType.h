#pragma once

#include <iostream>

typedef int ItemType;
struct NodeType;

class FullStack
// Exception class thrown by Push when stack is full.
{};

class EmptyStack
// Exception class thrown by Pop and Top when stack is emtpy.
{};

class StackType
{
friend std::ostream& operator<<(std::ostream& os, const StackType& other);
public:
	StackType();
	~StackType();

	bool IsFull() const;
	bool IsEmpty() const;
	void Push(ItemType item);
	void Pop();
	ItemType Top();
	void ReplaceItem(const ItemType& oldItem, const ItemType& newItem);
	void Copy(StackType& other);

private:
	NodeType* mTopPtr;
};

struct NodeType
{
	ItemType mInfo;
	NodeType* mNext;
};