#pragma once

class FullQueue
{};  

class EmptyQueue
{};  

typedef int ItemType;

namespace lab1_4
{
	class QueType
	{
	public: 
		QueType();
		QueType(unsigned int max);
		~QueType();

		void MakeEmpty();
		bool IsEmpty() const;
		bool IsFull() const;
		void Enqueue(ItemType newItem);
		void Dequeue(ItemType& item);
		void ReplaceItem(const ItemType& oldItem, const ItemType& newItem);
		bool Identical(const QueType& other) const;

		unsigned int Length() const;
	private:
		const unsigned int mMaxQue;
		unsigned int mFront;
		unsigned int mRear;
		ItemType* mItems;
	};
}

namespace lab5_6
{
	class QueType
	{
	public: 
		QueType();
		QueType(unsigned int capacity);
		~QueType();

		void MakeEmpty();
		bool IsEmpty() const;
		bool IsFull() const;
		void Enqueue(ItemType newItem);
		void Dequeue(ItemType& itemToDequeue);
		void MinDequeue(ItemType& itemToDequeue);
	private:
		unsigned int mCapacity;
		unsigned int mLength;
		unsigned int mFront;
		unsigned int mRear;
		ItemType* mItems;
		int mMinIndex;
	};
}