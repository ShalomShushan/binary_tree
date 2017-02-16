 //***************************************************************************************************
//
//		File:			Tree.h
//		
//		Student:		Shalom Shushan
//
//		Assignment:	 	Program  #6		
//
//		Course Name:		Data Structures II
//
//		Course Number:		COSC 3100 - 01
//
//		Due:			May 6th, 2016
//		
//*****************************************************************************************************

#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

template <class DT>
struct TreeNode
{
	TreeNode<DT>* left;
	TreeNode<DT>* right;
	DT info;
};

template <class DT>
class Tree
{
private:
	//private members//
	TreeNode<DT>* tree;
	TreeNode<DT>* pNew;

	//private functions//
	void addBST(TreeNode<DT>*& root, TreeNode<DT>* newNode, bool& isAdded);
	void updateNode(TreeNode<DT>* root, DT& item, bool& found);
	void deleteBST(TreeNode<DT>*& root, DT& item,bool& isdeleted);
	void searchTree(TreeNode<DT>* root, DT& item, bool& found);
	int countNodes(TreeNode<DT>* root);
	TreeNode<DT>* smallestNode (TreeNode<DT>* root);
	TreeNode<DT>* largestNode(TreeNode<DT>* root);
	int height(TreeNode<DT>* root);
	void inOrder(TreeNode<DT>* root);
	void preOrder(TreeNode<DT>* root);
	void postOrder(TreeNode<DT>* root);
	void  graphAux(int indent, TreeNode<DT>* root);	
	int max(int fisrt, int second);
public:
	//public functions//
	Tree();
	bool addItem(DT& item);
	bool updateList(DT& item);
	bool deleteItem(DT& item);
	bool searchItem(DT& item);
	int getNumOfNodes();
	DT& getSmallest();
	DT& getLargest();
	int getHeight();
	void displayAscending();
	void displayPreorder();
	void displayPostorder();
	void displayTree(int indent);
	int getTreeBalance();

};

/*********************   Private functions   ************************/

template <class DT>
void Tree<DT>::addBST(TreeNode<DT>*& root, TreeNode<DT>* newNode, bool& isAdded)
{
	if (root == NULL)
	{
		root = newNode;
		isAdded = true;
	}
	else
	{
		if (newNode->info < root->info)
		{
			addBST(root->left, newNode, isAdded);
		}
		else if (newNode->info > root->info)
		{
			addBST(root->right, newNode, isAdded);
		}
		else
		{
			isAdded = false;
		}
	}
}

template <class DT>
void Tree<DT>::updateNode(TreeNode<DT>* root, DT& item, bool& found)
{
	if (root == NULL)
	{
		found = false;
	}
	else if (item < root ->info)	
	{
		updateNode (root ->left, item, found);
	}
	else if (item > root ->info)	
	{
		updateNode (root ->right, item, found); 
	}
	else
	{
		root->info = item;
		found = true;
	}
}

template <class DT>
void Tree<DT>::deleteBST(TreeNode<DT>*& root, DT& item, bool& isdeleted)
{
	TreeNode<DT>* tempPtr;

	if (item < root->info)
	{
		if(root->left != NULL)							// I added those if statements instead of calling search before I delete, otherwise it tries to go left from a NULL //
		{												// I realize I could just call search before I delete, I just thought it's simpler //
			deleteBST(root->left, item, isdeleted); 
		}
	}
	else if (item > root->info)
	{	
		if(root->right != NULL) // Added by me
		{
			deleteBST(root->right, item, isdeleted);  
		}
	}
	else
	{
		if (root->left == NULL)
		{
			tempPtr = root;
			root = root->right;
			delete tempPtr;
			isdeleted = true;
		}
		else if (root->right == NULL)
		{
			tempPtr = root;
			root = root->left;
			delete tempPtr;
			isdeleted = true;
		}
		else
		{
			tempPtr = root->left;

			while(tempPtr->right != NULL)
			{
				tempPtr = tempPtr->right;
			}

			root->info = tempPtr->info;
			deleteBST(root->left,tempPtr->info,isdeleted);
		}
	}
}

template <class DT>
void Tree<DT>::searchTree(TreeNode<DT>* root, DT& item, bool& found)
{
	if (root == NULL)
	{
		found = false;
	}
	else if (item < root ->info)	
	{
		searchTree (root ->left, item, found);  
	}
	else if (item > root ->info)	
	{
		searchTree (root ->right, item, found); 
	}
	else
	{
		item = root->info;
		found = true;
	}
}

template <class DT>
void Tree<DT>::preOrder(TreeNode<DT>* root)
{
	if (root!=NULL)
	{
		cout << root->info;
		preOrder(root->left);
		preOrder(root->right);
	}
}

template <class DT>
void Tree<DT>::inOrder(TreeNode<DT>* root)
{
	if (root!=NULL)
	{
		inOrder(root->left);
		cout << root->info;
		inOrder(root->right);
	}
}

template <class DT>
void Tree<DT>::postOrder(TreeNode<DT>* root)
{
	if (root!=NULL)
	{
		postOrder(root->left);
		postOrder(root->right);
		cout << root->info;
	}
}

template <class DT>
TreeNode<DT>* Tree<DT>::smallestNode(TreeNode<DT>* root)
{
	if (root->left == NULL)
	{
		return root;
	}
	else
	{
		return smallestNode(root->left);
	}
}

template <class DT>
TreeNode<DT>* Tree<DT>::largestNode(TreeNode<DT>* root)
{
	if (root->right == NULL)
	{
		return root;
	}
	else
	{
		return largestNode(root->right);
	}
}

template<class DT>
int Tree<DT>::max(int first, int second)
{
	if(first > second)
		return first;
	else
		return second;
}

template <class DT>
int Tree<DT>::height(TreeNode<DT>* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(height(root->left), height(root->right));
	}
}

template<class DT>
int Tree<DT>::countNodes(TreeNode<DT>* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return countNodes(root->left) +	countNodes(root->right) + 1;
	}
}

template<class DT>
void  Tree<DT>::graphAux(int indent, TreeNode<DT>* root)
{
	if (root != 0)
	{
		graphAux(indent + 8, root->right);
		cout << setw(indent) << " " << root->info << endl;
		graphAux(indent + 8, root->left);
	}
}

/*********************   Public functions   ************************/

template <class DT>
Tree<DT>::Tree()
{
	tree = NULL;
	pNew = NULL;
}

template <class DT>
bool Tree<DT>::addItem(DT& item)
{
	bool isAdded;

	pNew = new TreeNode<DT>;
	pNew->left = NULL;
	pNew->right = NULL;

	pNew->info = item;
	addBST(tree, pNew, isAdded);

	return isAdded;
}

template <class DT>
bool Tree<DT>::updateList(DT& item)
{
	bool isFound;

	updateNode(tree, item, isFound);

	return isFound;
}

template <class DT>
bool Tree<DT>::deleteItem(DT& item)
{
	bool isdeleted = false;

	deleteBST(tree, item, isdeleted);

	return isdeleted;
}

template <class DT>
bool Tree<DT>::searchItem(DT& item)
{
	bool isFound;

	searchTree(tree, item, isFound);

	return isFound;
}

template <class DT>
int Tree<DT>::getNumOfNodes()
{
	return countNodes(tree);
}

template <class DT>
DT& Tree<DT>::getSmallest()
{
	TreeNode<DT>* temp = smallestNode(tree);
	return temp->info;
}

template <class DT>
DT& Tree<DT>::getLargest()
{
	TreeNode<DT>* temp = largestNode(tree);
	return temp->info;
}

template <class DT>
int Tree<DT>::getHeight()
{
	return height(tree);
}

template <class DT>
void Tree<DT>::displayAscending()
{
	inOrder(tree);
}

template <class DT>
void Tree<DT>::displayPreorder()
{
	preOrder(tree);
}

template <class DT>
void Tree<DT>::displayPostorder()
{
	postOrder(tree);
}

template <class DT>
void Tree<DT>::displayTree(int i)
{
	graphAux(i, tree);
}

template<class DT>
int Tree<DT>::getTreeBalance()
{
	if(tree == NULL)
	{
		return 0;
	}

	int leftHeight,
		rightHeight;

	leftHeight = height(tree->left);
	rightHeight = height(tree->right);

	if((leftHeight - rightHeight) == 1)
	{
		return 1;
	}
	else if ((leftHeight - rightHeight) == -1)
	{
		return -1;
	}
	else if ((leftHeight - rightHeight) == 0)
	{
		return 0;
	}

	return 99;
}