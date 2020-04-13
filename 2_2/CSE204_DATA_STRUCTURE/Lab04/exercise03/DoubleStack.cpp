#include "DoubleStack.h"

inline size_t GetNumberDigit(int number)
{
	size_t digit = 1;

	while(number / 10 > 0)
	{
		number /= 10;
		++digit;
	}

	return digit;
}

DoubleStack::DoubleStack()
	: mTopBelowEqualKey(0), mTopAboveKey(MAX_ITEMS - 1)
{
}

DoubleStack::DoubleStack(const DoubleStack& other)
{
	if (mStack != other.mStack)
	{
		mTopBelowEqualKey = other.mTopBelowEqualKey;
		mTopAboveKey = other.mTopAboveKey;

		for (size_t item = 0; item < mTopBelowEqualKey; ++item)
		{
			mStack[item] = other.mStack[item];
		}

		for (size_t item = MAX_ITEMS - 1; item > mTopAboveKey; --item)
		{
			mStack[item] = other.mStack[item];
		}
	}

}

DoubleStack& DoubleStack::operator=(const DoubleStack& other)
{
	if (mStack != other.mStack)
	{
		mTopBelowEqualKey = other.mTopBelowEqualKey;
		mTopAboveKey = other.mTopAboveKey;

		for (size_t item = 0; item < mTopBelowEqualKey; ++item)
		{
			mStack[item] = other.mStack[item];
		}
		
		for (size_t item = MAX_ITEMS - 1; item > mTopAboveKey; --item)
		{
			mStack[item] = other.mStack[item];
		}
	}

	return *this;
}

void DoubleStack::Clear()
{
	mTopBelowEqualKey = 0;
	mTopAboveKey = MAX_ITEMS - 1;
}

void DoubleStack::ClearBelowEqualKey()
{
	mTopBelowEqualKey = 0;
}

void DoubleStack::ClearAboveKey()
{
	mTopAboveKey = MAX_ITEMS - 1;
}

bool DoubleStack::IsEmpty() const
{
	return (mTopBelowEqualKey == 0 && mTopAboveKey == MAX_ITEMS - 1);
}

bool DoubleStack::IsBelowEqualKeyEmpty() const
{
	return (mTopBelowEqualKey == 0);
}

bool DoubleStack::IsAboveKeyEmpty() const
{
	return (mTopAboveKey == MAX_ITEMS - 1);
}

bool DoubleStack::IsFull() const
{
	return (mTopBelowEqualKey >= mTopAboveKey);
}

void DoubleStack::Push(int item)
{
	if (IsFull())
	{
		return;
	}

	if (item <= ITEM_KEY)
	{
		mStack[mTopBelowEqualKey++] = item;
	}
	else
	{
		mStack[mTopAboveKey--] = item;
	}
}

int DoubleStack::PopBelowEqualKey()
{
	assert(!IsEmpty());

	--mTopBelowEqualKey;

	return mStack[mTopBelowEqualKey];
}

int DoubleStack::PopAboveKey()
{
	assert(!IsEmpty());

	++mTopAboveKey;

	return mStack[mTopAboveKey];
}

void DoubleStack::Print() const
{
	if (mTopBelowEqualKey > 0)
	{
		std::cout << "PRINTING BELOW AND EQUAL KEY " << ITEM_KEY << std::endl;
	}

	for (size_t item = 0; item < mTopBelowEqualKey; ++item)
	{
		std::cout << "item[" << std::setw(GetNumberDigit(MAX_ITEMS)) << item << "]";
		std::cout << " = " << mStack[item] << std::endl;
	}

	if (mTopAboveKey < MAX_ITEMS - 1)
	{
		std::cout << "PRINTING ABOVE KEY " << ITEM_KEY << std::endl;
	}

	for (size_t item = MAX_ITEMS - 1; item > mTopAboveKey; --item)
	{
		std::cout << "item[" << std::setw(GetNumberDigit(MAX_ITEMS)) << item << "]";
		std::cout << " = " << mStack[item] << std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, const DoubleStack& rhs)
{
	if (rhs.mTopBelowEqualKey > 0)
	{
		os << "PRINTING BELOW AND EQUAL KEY " << ITEM_KEY << std::endl;
	}

	for (size_t item = 0; item < rhs.mTopBelowEqualKey; ++item)
	{
		os << "item[" << std::setw(GetNumberDigit(MAX_ITEMS)) << item << "]";
		os << " = " << rhs.mStack[item] << std::endl;
	}

	if (rhs.mTopAboveKey < MAX_ITEMS - 1)
	{
		os << "PRINTING ABOVE KEY " << ITEM_KEY << std::endl;
	}

	for (size_t item = MAX_ITEMS - 1; item > rhs.mTopAboveKey; --item)
	{
		os << "item[" << std::setw(GetNumberDigit(MAX_ITEMS)) << item << "]";
		os << " = " << rhs.mStack[item] << std::endl;
	}

	return os;
}