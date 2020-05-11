#pragma once

namespace hw7
{
	template <typename T>
	class Node;

	template <typename T>
	class Stack
	{
	public:
		Stack();
		Stack(const Stack& other);
		virtual ~Stack();

		Stack& operator=(const Stack& other);

		Stack& Copy(const Stack& other);
	private:
		unsigned int mSize;
		Node<T>* mTop;
	};

	template <typename T>
	Stack<T>::Stack()
		: mSize(0)
		, mTop(nullptr)
	{
	}

	template <typename T>
	Stack<T>::Stack(const Stack& other)
	{
		mSize = other.mSize;

		if (mTop != other.mTop)
		{
			mTop = new Node<T>(other.mTop->Data);

			Node<T>* tempNode = mTop;
			Node<T>* tempOtherNode = other.mTop->Next;

			for (size_t count = 0; tempOtherNode != nullptr && count < mSize; tempOtherNode = tempOtherNode->Next, ++count)
			{
				tempNode->Next = tempOtherNode;
				tempNode = new Node<T>(tempOtherNode->Data);
			}

			tempNode->Next = nullptr;
		}
	}

	template<typename T>
	Stack<T>::~Stack()
	{
		Node<T>* nodeToDelete = nullptr;

		while (mSize > 0 && mTop != nullptr)
		{
			nodeToDelete = mTop;
			mTop = mTop->Next;

			if (nodeToDelete != nullptr)
			{
				delete nodeToDelete;
				--mSize;
			}
		}
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack& other)
	{
		

		if (mTop != other.mTop)
		{
			if (mTop != nullptr)
			{
				Node<T>* nodeToDelete = nullptr;
				while (mSize > 0 && mTop != nullptr)
				{
					nodeToDelete = mTop;
					mTop = mTop->Next;

					if (nodeToDelete != nullptr)
					{
						delete nodeToDelete;
						nodeToDelete = nullptr;
						--mSize;
					}
				}	
			}

			mSize = other.mSize;
			mTop = new Node<T>(other.mTop->Data);

			Node<T>* tempNode = mTop;
			Node<T>* tempOtherNode = other.mTop->Next;

			for (size_t count = 0; tempOtherNode != nullptr && count < mSize; tempOtherNode = tempOtherNode->Next, ++count)
			{
				tempNode->Next = tempOtherNode;
				tempNode = new Node<T>(tempOtherNode->Data);
			}

			tempNode->Next = nullptr;
		}

		return *this;
	}

	template <typename T>
	Stack<T>& Stack<T>::Copy(const Stack& other)
	{
		return operator=(other);
	}
}