#pragma once

template <typename T> struct MwBinaryTree
{
	MwBinaryTree<T> *parent, *left, *right;
	T value;

	MwBinaryTree(void)
	{
		this->parent = 0;
		this->left = 0;
		this->right = 0;
	};

	MwBinaryTree(MwBinaryTree<T> *parent, T value)
	{
		this->parent = parent;
		this->value = value;
		this->left = 0;
		this->right = 0;
	};

	~MwBinaryTree(void)
	{
		if (this->left != 0)
			delete this->left;

		if (this->right != 0)
			delete this->right;
	};

	// Traverses the tree up in the hierarchy, searching for a parent branch with another child. In other words, searches for the closest ancestor where lineage splits
	MwBinaryTree<T> *FindSplittingParent(MwBinaryTree<T> *branch)
	{
		MwBinaryTree<T> *result = this->parent;

		while (result != 0)
		{
			if ((branch->parent->left != 0) && (branch->parent->right != 0))
				break;
		}

		return result;
	};

	//static MwBinaryTree<T> *FindLeftmostLeaf(MwBinaryTree<T> *branch)
	//{
	//	if (branch->left != 0)
	//		return MwBinaryTree<T>::FindLeftmostLeaf(branch->left);

	//	if (branch->right != 0)
	//		return MwBinaryTree<T>::FindLeftmostLeaf(branch->right);

	//	return branch;
	//};

	//static MwBinaryTree<T> *FindRightmostLeaf(MwBinaryTree<T> *branch)
	//{
	//	if (branch->right != 0)
	//		return MwBinaryTree<T>::FindRightmostLeaf(branch->right);

	//	if (branch->left != 0)
	//		return MwBinaryTree<T>::FindRightmostLeaf(branch->left);

	//	return branch;
	//};

	MwBinaryTree<T> *FindLeftmostLeaf()
	{
		MwBinaryTree<T> *result = this;
		
		for (;;)
		{
			if (result->left != 0)
				result = result->left;

			else if (result->right != 0)
				result = result->right;

			else 
				break;
		}

		return result;
	}	
	
	MwBinaryTree<T> *FindRightmostLeaf()
	{
		MwBinaryTree<T> *result = this;
		
		for (;;)
		{
			if (result->right != 0)
				result = result->right;

			else if (result->left != 0)
				result = result->left;

			else
				break;
		}

		return result;
	}

	bool AddLeft(T value)
	{
		if (this->left != 0)
			return false;

		this->left = new MwBinaryTree<T>(this, value);
	};	
	
	bool AddRight(T value)
	{
		if (this->right != 0)
			return false;

		this->right = new MwBinaryTree<T>(this, value);
	};

	void RemoveLeft()
	{
		if (this->left == 0)
			return;

		delete this->left;
		this->left = 0;
	};

	void RemoveRight()
	{
		if (this->right == 0)
			return;

		delete this->right;
		this->right = 0;
	};
};