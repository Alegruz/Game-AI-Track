#pragma once

// typedef struct tree_node* TreeNode;

// typedef struct ll_heap_type* LLHeapType;

#include <cassert>
#include <cstddef>
#include <iostream>

void SwapInt(int& i, int& j);

typedef struct tree_node
{
	int info;
	struct tree_node* left;
	struct tree_node* right;
	struct tree_node* parent;
} *TreeNode;

typedef struct ll_heap_type
{
	void ReheapUp(TreeNode node)
	{
		// std::cout << "REHEAPUP CALLED" << std::endl;
		if (node == nullptr)
		{
			return;
		}

		ReheapUp(node->left);
		ReheapUp(node->right);

		if (node->left != nullptr)
		{
			if (node->left->info > node->info)
			{
				SwapInt(node->left->info, node->info);
			}
		}
		if (node->right != nullptr)
		{
			if (node->right->info > node->info)
			{
				SwapInt(node->left->info, node->info);
			}
		}
	}

	void ReheapDown(void)
	{
	}
	TreeNode root;
} *LLHeapType;