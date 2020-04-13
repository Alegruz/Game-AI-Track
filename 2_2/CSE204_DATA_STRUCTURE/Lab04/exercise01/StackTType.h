#pragma once

template<class ItemType>	
class StackType
{
public:
    StackType();
	virtual ~StackType();

    bool IsFull() const;
    bool IsEmpty() const;
    void Push(const ItemType& item);
    void Pop();
    const ItemType& Top();      
private:
    unsigned int mTop;
	unsigned int mCapacity;
    ItemType* mStack;
};

template<class ItemType>
StackType<ItemType>::StackType()
	: mTop(0), mCapacity(8), mStack(new ItemType[mCapacity])
{
}

template<class ItemType>
StackType<ItemType>::~StackType()
{
	delete[] mStack;
}

template<class ItemType>
bool StackType<ItemType>::IsEmpty() const
{
  return (mTop == 0);
}

template<class ItemType>
bool StackType<ItemType>::IsFull() const
{
  return (mTop == mCapacity);
}

template<class ItemType>
void StackType<ItemType>::Push(const ItemType& newItem) 
{
	if (IsFull())
	{
		ItemType tempStack[mTop];
		for (unsigned int item = 0; item < mTop; ++item)
		{
			tempStack[item] = mStack[item];
		}

		delete[] mStack;

		mCapacity *= 2;
		mStack = new ItemType[mCapacity];

		for (unsigned int item = 0; item < mTop; ++item)
		{
			mStack[item] = tempStack[item];
		}
	}

	mStack[mTop++] = newItem;
}

template<class ItemType>
void StackType<ItemType>::Pop()
{
	if (IsEmpty())
	{
		return;
	}

	--mTop;
}

template<class ItemType>
const ItemType& StackType<ItemType>::Top()
{
	if (IsEmpty())
	{
		return ItemType();
	}

	return mStack[mTop - 1];
}  
