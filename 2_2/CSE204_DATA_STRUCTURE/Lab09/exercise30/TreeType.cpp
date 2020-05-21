#include "TreeType.h"

bool TreeType::IsFull() const
// Returns true if there is no room for another item
//  on the free store; false otherwise.
{
	TreeNode *location;
	try
	{
		location = new TreeNode;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

bool Imp_IsBST(TreeNode* tree, ItemType& min, ItemType& max);

bool TreeType::IsBST() const
{
	ItemType min = mRoot->info;
	ItemType max = mRoot->info;
	return Imp_IsBST(mRoot, min, max);
}


bool Imp_IsBST(TreeNode* tree, ItemType& min, ItemType& max)
{
	bool bIsBST = true;

	if (tree == nullptr)
	{
		return true;
	}

	if (tree->left != nullptr)
	{
		bIsBST = Imp_IsBST(tree->left, min, max);
		if (!bIsBST || tree->info < tree->left->info)
		{
			return false;
		}

		min = tree->left->info;
	}
	

	if (tree->right != nullptr)
	{
		bIsBST = Imp_IsBST(tree->right, min, max);
		if (!bIsBST || tree->info > tree->right->info)
		{
			return false;
		}

		max = tree->right->info;
	}

	return true;
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
	return mRoot == nullptr;
}

int CountNodes(TreeNode *tree);

int TreeType::LengthIs() const
// Calls recursive function CountNodes to count the
// nodes in the tree.
{
	return CountNodes(mRoot);
}

int CountNodes(TreeNode *tree)
// Post: returns the number of nodes in the tree.
{
	if (tree == nullptr)
		return 0;
	else
		return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode *tree,
			  ItemType &item, bool &found);

void TreeType::RetrieveItem(ItemType &item, bool &found)
// Calls recursive function Retrieve to search the tree for item.
{
	Retrieve(mRoot, item, found);
}

void Retrieve(TreeNode *tree,
			  ItemType &item, bool &found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise found is false and item is unchanged.
{
	if (tree == nullptr)
		found = false; // item is not found.
	else if (item < tree->info)
		Retrieve(tree->left, item, found); // Search left subtree.
	else if (item > tree->info)
		Retrieve(tree->right, item, found); // Search right subtree.
	else
	{
		item = tree->info; // item is found.
		found = true;
	}
}

void Insert(TreeNode *&tree, ItemType item);

void TreeType::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	Insert(mRoot, item);
}

void Insert(TreeNode *&tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
	if (tree == nullptr)
	{ // Insertion place found.
		tree = new TreeNode;
		tree->right = nullptr;
		tree->left = nullptr;
		tree->info = item;
	}
	else if (item < tree->info)
		Insert(tree->left, item); // Insert in left subtree.
	else
		Insert(tree->right, item); // Insert in right subtree.
}
void DeleteNode(TreeNode *&tree);

void Delete(TreeNode *&tree, ItemType item);

void TreeType::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	Delete(mRoot, item);
}

void Delete(TreeNode *&tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
	std::cout << "tree: " << tree->info << " item: " << item << std::endl;
	if (item < tree->info)
		Delete(tree->left, item); // Look in left subtree.
	else if (item > tree->info)
		Delete(tree->right, item); // Look in right subtree.
	else
		DeleteNode(tree); // Node found; call DeleteNode.
}

void GetPredecessor(TreeNode *tree, ItemType &data);

TreeNode* PtrToSuccessorRecursive(TreeNode*& tree)
{
	if (tree->left != nullptr)
	{
		return PtrToSuccessorRecursive(tree->left);
	}
	else
	{
		TreeNode* tempNode = tree;
		tree = tree->right;
	
		return tempNode;
	}
}


TreeNode *PtrToSuccessor(TreeNode *&tree)
{
	while (tree->left != nullptr)
	{
		tree = tree->left;
	}

	TreeNode* tempNode = tree;
	tree = tree->right;
	return tempNode;
}

void DeleteNode(TreeNode *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-nullptr child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
	ItemType data;
	TreeNode *tempPtr;

	tempPtr = tree;
	if (tree->left == nullptr)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == nullptr)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		TreeNode* tempNode = tree;
		TreeNode* successorNode = PtrToSuccessor(tempNode->right);
		data = successorNode->info;
		tree->info = data;
		delete successorNode;
	}
}

void GetPredecessor(TreeNode *tree, ItemType &data)
// Sets data to the info member of the right-most node in tree.
{
	while (tree->right != nullptr)
		tree = tree->right;
	data = tree->info;
}

void PrintTree(TreeNode *tree, std::ofstream &outFile)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != nullptr)
	{
		PrintTree(tree->left, outFile); // Print left subtree.
		outFile << tree->info;
		PrintTree(tree->right, outFile); // Print right subtree.
	}
}

void TreeType::Print(std::ofstream &outFile) const
// Calls recursive function Print to print items in the tree.
{
	PrintTree(mRoot, outFile);
}

TreeType::TreeType()
{
	mRoot = nullptr;
}

void Destroy(TreeNode *&tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(mRoot);
}

void Destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
	if (tree != nullptr)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

void TreeType::MakeEmpty()
{
	Destroy(mRoot);
	mRoot = nullptr;
}

void CopyTree(TreeNode *&copy,
			  const TreeNode *originalTree);

TreeType::TreeType(const TreeType &originalTree)
// Calls recursive function CopyTree to copy originalTree
//  into mRoot.
{
	CopyTree(mRoot, originalTree.mRoot);
}

void TreeType::operator=(const TreeType &originalTree)
// Calls recursive function CopyTree to copy originalTree
// into mRoot.
{
	{
		if (&originalTree == this)
			return;		// Ignore assigning self to self
		Destroy(mRoot); // Deallocate existing tree nodes
		CopyTree(mRoot, originalTree.mRoot);
	}
}
void CopyTree(TreeNode *&copy,
			  const TreeNode *originalTree)
// Post: copy is the mRoot of a tree that is a duplicate
//       of originalTree.
{
	if (originalTree == nullptr)
		copy = nullptr;
	else
	{
		copy = new TreeNode;
		copy->info = originalTree->info;
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);
	}
}
// Function prototypes for auxiliary functions.

void PreOrder(TreeNode *, QueType &);
// Enqueues tree items in preorder.

void InOrder(TreeNode *, QueType &);
// Enqueues tree items in inorder.

void PostOrder(TreeNode *, QueType &);
// Enqueues tree items in postorder.

void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in
// the desired order.
{
	switch (order)
	{
	case PRE_ORDER:
		PreOrder(mRoot, mPreQue);
		break;
	case IN_ORDER:
		InOrder(mRoot, mInQue);
		break;
	case POST_ORDER:
		PostOrder(mRoot, mPostQue);
		break;
	}
}

void PreOrder(TreeNode *tree,
			  QueType &preQue)
// Post: preQue contains the tree items in preorder.
{
	if (tree != nullptr)
	{
		preQue.Enqueue(tree->info);
		PreOrder(tree->left, preQue);
		PreOrder(tree->right, preQue);
	}
}

void InOrder(TreeNode *tree,
			 QueType &inQue)
// Post: inQue contains the tree items in inorder.
{
	if (tree != nullptr)
	{
		InOrder(tree->left, inQue);
		inQue.Enqueue(tree->info);
		InOrder(tree->right, inQue);
	}
}

void PostOrder(TreeNode *tree,
			   QueType &postQue)
// Post: postQue contains the tree items in postorder.
{
	if (tree != nullptr)
	{
		PostOrder(tree->left, postQue);
		PostOrder(tree->right, postQue);
		postQue.Enqueue(tree->info);
	}
}

void TreeType::GetNextItem(ItemType &item,
						   OrderType order, bool &finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true;
//       otherwise finished is false.
{
	finished = false;
	switch (order)
	{
	case PRE_ORDER:
		mPreQue.Dequeue(item);
		if (mPreQue.IsEmpty())
			finished = true;
		break;
	case IN_ORDER:
		mInQue.Dequeue(item);
		if (mInQue.IsEmpty())
			finished = true;
		break;
	case POST_ORDER:
		mPostQue.Dequeue(item);
		if (mPostQue.IsEmpty())
			finished = true;
		break;
	}
}

int Imp_LeafCount(TreeNode* tree);

int TreeType::LeafCount() const
{
	return Imp_LeafCount(mRoot);
}

int Imp_LeafCount(TreeNode* tree)
{
	if (tree == nullptr)
	{
		return 0;
	}
	else if (tree->left == nullptr && tree->right == nullptr)
	{
		return 1;
	}
	else
	{
		return Imp_LeafCount(tree->left) + Imp_LeafCount(tree->right);
	}
}