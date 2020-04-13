#pragma once

#include <cassert>
#include <iomanip>
#include <iostream>

const int MAX_ITEMS = 200;
const int ITEM_KEY = 1000;

class DoubleStack
{
	friend std::ostream& operator<<(std::ostream& os, const DoubleStack& rhs);
public:
	DoubleStack();
	DoubleStack(const DoubleStack& other);
	virtual ~DoubleStack() = default;

	DoubleStack& operator=(const DoubleStack& other);

	void Clear();
	void ClearBelowEqualKey();
	void ClearAboveKey();
	bool IsEmpty() const;
	bool IsBelowEqualKeyEmpty() const;
	bool IsAboveKeyEmpty() const;
	bool IsFull() const;
	void Push(int item);
	int Pop();
	int PopBelowEqualKey();
	int PopAboveKey();
	void Print() const;
private:
	size_t mTopBelowEqualKey;
	size_t mTopAboveKey;
	int mStack[MAX_ITEMS];
};