#pragma once

namespace hw7
{
	template<typename T>
	class Node
	{
	public:
		Node(const T& data);
		T Data;
		Node<T>* Next;
	};

	template<typename T>
	Node<T>::Node(const T& data)
		: Data(data), Next(nullptr)
	{
	}
}