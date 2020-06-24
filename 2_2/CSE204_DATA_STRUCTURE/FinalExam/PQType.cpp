#include <cmath>
#include <iostream>

#include "PQType.h"

PQType::PQType(int max)
	: mLength(0),
	mItems(new (struct ll_heap_type)()),
	mMaxItems(max)
{
	mItems->root = nullptr;
}

TreeNode GetParent(TreeNode node)
{
	return node->parent;
}

TreeNode PQType::FindParent(int i)
{
	// std::cout << "FINDPARENT: called " << i << std::endl;
	int parentIndexArray[mLength];
	int index = 0;
	parentIndexArray[index] = i;

	do
	{
		// std::cout << parentIndexArray[index] << " " << std::boolalpha << (parentIndexArray[index] >= 0) << std::endl;
		// std::cout << static_cast<float>(parentIndexArray[index - 1] - 1) * 0.5 << " ";
		// std::cout << static_cast<int>(floor(static_cast<float>(parentIndexArray[index - 1] - 1) * 0.5)) << std::endl;
		parentIndexArray[index + 1] = static_cast<int>(floor(static_cast<float>(parentIndexArray[index] - 1) * 0.5));
		++index;
	} while(parentIndexArray[index] >= 0);
	--index;

	for (int j = 0; j <= index; ++j)
	{
		std::cout << parentIndexArray[j] << " ";
	}
	std::cout << "index: " << index << " item index: " << i << std::endl;

	TreeNode tempNode = mItems->root;
	int rootIndex = 0;
	while (index >= 0)
	{
		if (parentIndexArray[index] == 0)
		{
			--index;
			continue;
		}
		std::cout << "index to check: " << parentIndexArray[index] << std::endl;

		if (parentIndexArray[index] == rootIndex * 2 + 1)
		{
			std::cout << "Going from " << tempNode->info << " to left";
			if (tempNode->left != nullptr)
			{
				std::cout << tempNode->left->info;
				tempNode = tempNode->left;
			}
			else
			{
				std::cout << std::endl;
				break;
			}
			
			std::cout << std::endl;
			rootIndex = rootIndex * 2 + 1;
		}

		if (parentIndexArray[index] == rootIndex * 2 + 2)
		{
			std::cout << "Going from " << tempNode->info << " to right";
			if (tempNode->right != nullptr)
			{
				std::cout << tempNode->right->info;
				tempNode = tempNode->right;
			}
			else
			{
				std::cout << std::endl;
				break;
			}
			
			std::cout << std::endl;
			rootIndex = rootIndex * 2 + 2;
		}

		--index;
	}

	return tempNode;
}

void EmptyTree(TreeNode node)
{
	if (node == nullptr)
	{
		return;
	}

	EmptyTree(node->left);
	EmptyTree(node->right);

	delete node;
	node = nullptr;
}

void PQType::MakeEmpty()
{
	mLength = 0;
	EmptyTree(mItems->root);
}

PQType::~PQType()
{
	delete mItems;
}

void PQType::Dequeue(int& item)
// Post: element with highest priority has been removed
//       from the queue; a copy is returned in item.
{
	if (mLength <= 0)
		throw EmptyPQ();
	else
	{
		item = mItems->root->info;

		TreeNode parent = FindParent(mLength - 1);

		mItems->root->info = parent->info;
		--mLength;
		mItems->ReheapDown();
	}
}

void PQType::Enqueue(int newItem)
// Post: newItem is in the queue.
{
	std::cout << "ENQUEUE CALLED" << std::endl;
	if (mLength == mMaxItems)
		throw FullPQ();
	else
	{
		TreeNode parent = FindParent(mLength);
		if (parent == nullptr)
		{
			// std::cout << "ENQUEUE: Empty Queue" << std::endl;
			mItems->root = new (struct tree_node);
			mItems->root->info = newItem;
			// std::cout << "ENQUEUE: Added " << newItem << std::endl;
			mItems->root->left = nullptr;
			mItems->root->right = nullptr;
		}
		else
		{
			std::cout << "ENQUEUE: Parent is " << parent->info << std::endl;
			if (parent->left == nullptr)
			{
				std::cout << "ENQUEUE: Adding new Node to the left of parent " << parent->info << std::endl;
				parent->left = new (struct tree_node);
				parent->left->info = newItem;
				std::cout << "ENQUEUE: Added " << newItem << std::endl;
				parent->left->parent = parent;
				parent->left->left = nullptr;
				parent->left->right = nullptr;
			}
			else if (parent->right == nullptr)
			{
				std::cout << "ENQUEUE: Addign new Node to the right of parent " << parent->info << std::endl;
				parent->right = new (struct tree_node);
				parent->right->info = newItem;
				std::cout << "ENQUEUE: Added " << newItem << std::endl;
				parent->right->parent = parent;
				parent->right->left = nullptr;
				parent->right->right = nullptr;
			}
		}
		
		++mLength;
		std::cout << "ENQUEUE: Length now " << mLength << std::endl;
		mItems->ReheapUp(mItems->root);
	}
}

bool PQType::IsFull() const
// Post: Returns true if the queue is full; false, otherwise.
{
	return mLength == mMaxItems;
}

bool PQType::IsEmpty() const
// Post: Returns true if the queue is empty; false, otherwise.
{
	return mLength == 0;
}
