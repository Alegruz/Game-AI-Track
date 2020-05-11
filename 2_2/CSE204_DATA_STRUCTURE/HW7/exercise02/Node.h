#pragma once

#include <memory>

namespace hw7
{
	template<typename T>
	class Node
	{
	public:
		Node(const T& data);
		virtual ~Node();
		T Data;
		T* Next;
	};

	template<typename T>
	Node<T>::Node(const T& data)
		: Data(data), Next(nullptr)
	{
	}

	template<typename T>
	Node<T>::~Node()
	{
		delete Next;
	}
}