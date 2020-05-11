#pragma once

namespace hw7
{
	template<typename T>
	class Node;

	template<typename T>
	class CircularLinkedList
	{
	public:
		CircularLinkedList();
		CircularLinkedList(const CircularLinkedList& other);
		virtual ~CircularLinkedList();

	private:
		Node<T>* mFirstNode;
		unsigned int mSize;
	};

	template<typename T>
	CircularLinkedList<T>::CircularLinkedList()
		: mFirstNode(nullptr)
		, mSize(0)
	{
	}

	template<typename T>
	CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList& other)
	{
		mSize = other.mSize;

		if (mFirstNode != other.mFirstNode)
		{
			mFirstNode = new Node<T>(other.mFirstNode->Data);

			Node<T>* tempPtr = mFirstNode;
			Node<T>* tempOtherPtr = other.mFirstNode->Next;

			for (size_t count = 0; tempOtherPtr != nullptr && count < mSize; tempOtherPtr = tempOtherPtr->Next, ++count)
			{
				tempPtr->Next = tempOtherPtr;
				tempPtr = new Node<T>(tempOtherPtr->Data);
			}

			tempPtr->Next = nullptr;
		}
	}

	template<typename T>
	CircularLinkedList<T>::~CircularLinkedList()
	{
		Node<T>* nodeToDelete = nullptr;

		while (mSize > 0 && mFirstNode != nullptr)
		{
			nodeToDelete = mFirstNode;
			mFirstNode = mFirstNode->Next;

			if (nodeToDelete != nullptr)
			{
				delete nodeToDelete;
				--mSize;
			}
		}
	}
}