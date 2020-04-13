#pragma once

#include "ItemType.h"

#include <iostream>

class FullStack
{};

class EmptyStack
{};

class StackType
{
	friend std::ostream& operator<<(std::ostream& os, const StackType& rhs);
public:
	StackType();
	StackType(const StackType& other) = default;
	virtual ~StackType() = default;

	StackType& operator=(const StackType& other) = default;

	bool IsFull() const;
	bool IsEmpty() const;
	void Push(const ItemType& item);
	void Pop();
	const ItemType& Top() const;
	void ReplaceItem(const ItemType& oldItem, const ItemType& newItem);
private:
	size_t mTop;
	ItemType mItems[MAX_ITEMS];
};

