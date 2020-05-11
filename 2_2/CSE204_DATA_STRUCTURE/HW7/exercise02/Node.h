#pragma once

#include <memory>

namespace hw7
{
	template<typename T>
	class Node
	{
	public:
		Node(std::unique_ptr<T> data);
		std::unique_ptr<T> Data;
		std::shared_ptr<Node<T>> Next;
	};

	template<typename T>
	Node<T>::Node(std::unique_ptr<T> data)
		: Data(std::move(data))
	{
		Next = nullptr;
	}
}