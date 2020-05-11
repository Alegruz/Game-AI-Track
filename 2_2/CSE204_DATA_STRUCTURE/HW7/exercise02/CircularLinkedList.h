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
		CircularLinkedList(T*&& node);
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
	CircularLinkedList<T>::CircularLinkedList(T*&& node)
		: mFirstNode(new Node<T>(node->Data))
		, mSize(0)
	{
		mFirstNode->Next = nullptr;
		node = nullptr;
	}

	template<typename T>
	CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList& other)
	{
		if (mFirstNode != other.mFirstNode)
		{
			mFirstNode = new Node<T>(other.mFirstNode->Data);

			Node<T>* tempPtr = mFirstNode;
			Node<T>* tempOtherPtr = other.mFirstNode->Next;

			for (; tempOtherPtr != nullptr; tempOtherPtr = tempOtherPtr->Next)
			{
				tempPtr->Next = tempOtherPtr;
				tempPtr = new Node<T>(tempOtherPtr->Data);
			}

			tempPtr->Next = nullptr;
		}

		mSize = other.mSize;
	}

	template<typename T>
	CircularLinkedList<T>::~CircularLinkedList()
	{
		Node<T>* nodeToDelete = nullptr;

		while (mFirstNode != nullptr)
		{
			nodeToDelete = mFirstNode;
			mFirstNode = mFirstNode->Next;

			delete nodeToDelete;
		}
	}
}