#include <cassert>
#include <iostream>

#include "TreeType.h"


bool SimilarTrees(TreeNode*& tr1, TreeNode*& tr2)
{
	bool bResult = false;

	std::cout << "info: " << tr1->info << " ~ " << tr2->info << std::endl;

	if (tr1->info == tr2->info)
	{
		bResult = true;
	}
	else
	{
		return false;
	}

	// only left exists
	if (tr1->right == nullptr && tr1->left != nullptr && tr2->right == nullptr && tr2->left != nullptr)
	{
		bResult = SimilarTrees(tr1->left, tr2->left);
	}	// only right exists
	else if (tr1->left == nullptr && tr1->right != nullptr && tr2->left == nullptr && tr2->right != nullptr)
	{
		bResult = SimilarTrees(tr1->right, tr2->right);
	}	// both exists
	else if (tr1->left != nullptr && tr1->right != nullptr && tr2->left != nullptr && tr2->right != nullptr)
	{
		bResult = SimilarTrees(tr1->left, tr2->left) && SimilarTrees(tr1->right, tr2->right);
	}	// both doesn't exists
	else if (tr1->left == nullptr && tr1->right == nullptr && tr2->left == nullptr && tr2->right == nullptr)
	{
		return bResult;
	}
	else
	{
		return false;
	}
	
	return bResult;
}

int main()
{
	TreeNode tn4 = {'a'-1, nullptr, nullptr};
	TreeNode tn3 = {'d', nullptr, nullptr};
	TreeNode tn2 = {'a', &tn4, nullptr};
	TreeNode tn1 = {'c', nullptr, &tn3};
	TreeNode* rn = new TreeNode({'b', &tn2, &tn1});

	TreeNode tn41 = {'a'-2, nullptr, nullptr};
	TreeNode tn31 = {'d', nullptr, nullptr};
	TreeNode tn21 = {'a', &tn41, nullptr};
	TreeNode tn11 = {'c', nullptr, &tn31};
	TreeNode* rn1 = new TreeNode({'b', &tn21, &tn11});

	std::cout << "result: " << std::boolalpha << SimilarTrees(rn, rn1) << std::endl;

	return 0;
}