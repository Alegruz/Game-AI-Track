#pragma once

#include <iostream>

class FullQueue
{};  

class EmptyQueue
{};  

template <class ItemType>
struct NodeType
{
	ItemType mInfo;
	NodeType* mNext;
};

namespace exercise02
{
	template <class ItemType>
	class QueType
	{
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const QueType<T>& other);
	public: 
		QueType();
		QueType(int max);
		~QueType();

		void MakeEmpty();
		bool IsEmpty() const;
		bool IsFull() const;
		void Enqueue(ItemType newItem);
		void Dequeue(ItemType& item);
		void ReplaceItem(const ItemType& oldItem, const ItemType& newItem);

	private:
		NodeType<ItemType>* mFront;
		NodeType<ItemType>* mRear;
	};

	template <class ItemType>
	QueType<ItemType>::QueType()
	{
		mFront = nullptr;
		mRear = nullptr;
	}

	template <class ItemType>
	void QueType<ItemType>::MakeEmpty()
	{
		NodeType<ItemType>* tempPtr;

		while (mFront != nullptr)
		{
			tempPtr = mFront;
			mFront = mFront->mNext;
			delete tempPtr;
		}
		mRear = nullptr;
	}

	template <class ItemType>
	QueType<ItemType>::~QueType()
	{
		MakeEmpty();
	}

	template<class ItemType>
	bool QueType<ItemType>::IsFull() const
	{
		NodeType<ItemType>* location;

		try
		{
			location = new NodeType<ItemType>;
			delete location;
			return false;
		}
		catch(std::bad_alloc exception)
		{
			return true;
		}
	}

	template <class ItemType>
	bool QueType<ItemType>::IsEmpty() const
	{
		return (mFront == nullptr);
	}

	template <class ItemType>
	void QueType<ItemType>::Enqueue(ItemType newItem)
	{
		if (IsFull())
		{
			throw FullQueue();
		}
		else
		{
			NodeType<ItemType>* newNode;

			newNode = new NodeType<ItemType>;
			newNode->mInfo = newItem;
			newNode->mNext = nullptr;
			if (mRear == nullptr)
			{
				mFront = newNode;
			}
			else
			{
				mRear->mNext = newNode;
			}
			mRear = newNode;
		}
	}

	template <class ItemType>
	void QueType<ItemType>::Dequeue(ItemType& item)
	{
		if (IsEmpty())
		{
			throw EmptyQueue();
		}
		else
		{
			NodeType<ItemType>* tempPtr;

			tempPtr = mFront;
			item = mFront->mInfo;
			mFront = mFront->mNext;
			if (mFront == nullptr)
			{
				mRear = nullptr;
			}
			delete tempPtr;
		}
	}

	template <class ItemType>
	void QueType<ItemType>::ReplaceItem(const ItemType& oldItem, const ItemType& newItem)
	{
		if (mFront == nullptr)
		{
			return;
		}

		NodeType<ItemType>* tempPtr = mFront;
		while (tempPtr != nullptr)
		{
			if (tempPtr->mInfo == oldItem)
			{
				tempPtr->mInfo = newItem;
			}

			tempPtr = tempPtr->mNext;
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const QueType<T>& other)
	{
		NodeType<T>* tempPtr = other.mFront;
		size_t index = 0;
		while (tempPtr != nullptr)
		{
			os << "Queue[" << index << "] = " << tempPtr->mInfo << std::endl;
			tempPtr = tempPtr->mNext;
			++index;
		}

		return os;
	}
}