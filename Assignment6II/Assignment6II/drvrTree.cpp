//***************************************************************************************************
//
//		File:			drvr.cpp
//		
//		Student:		Shalom Shushan
//
//		Assignment:	 	Program  # Extra credit 4		
//
//		Course Name:		Data Structures II
//
//		Course Number:		COSC 3100 - 01
//
//		Due:			May 3th, 2016
//
//
//		This program read data from a file and creates a BST. It has a menu that allows to
//		perform various actions on the tree.
//
//		Other files required: 
//			1.	Categories.csv – Data file
//			2.	Tree.h – The Tree class
//		
//*****************************************************************************************************

#include "Tree.h"
#include <string>
#include <fstream>

struct Category
{
	char code;
	string desc;

	Category()
	{
		code = NULL;
		desc = "";
	}

	bool operator<(Category& right)
	{
		if (code < right.code)
		{
			return true;
		}

		return false;
	}

	bool operator>(Category& right)
	{
		if (code > right.code)
		{
			return true;
		}

		return false;
	}

	friend ostream& operator <<(ostream& out, Category& item)
	{
		out << "Item code: " << item.code << endl
			<< "Item description: " << item.desc << endl << endl;

		return out;
	}
};

void readData(Tree<Category>& tree);
void showMenu(int &choice);
void addCategory(Tree<Category>& tree);
void updateCategory(Tree<Category>& tree);
void deleteCategory(Tree<Category>& tree);
void searchCategory(Tree<Category>& tree);
void CountCategories(Tree<Category>& tree);
void getSmallestCategory(Tree<Category>& tree);
void getLargestCategory(Tree<Category>& tree);
void getHeight(Tree<Category>& tree);
void displayAscending(Tree<Category>& tree);
void displayPreorder(Tree<Category>& tree);
void displayPostorder(Tree<Category>& tree);
void displayTree(Tree<Category>& tree, int indent);
void isBalanced(Tree<Category>& tree);

int main()
{
	int choice = 0;
	const int INDENT = 25;
	Tree<Category> tree;

	readData(tree);

	while(choice != 14)
	{
		showMenu(choice);

		switch(choice)
		{
		case 1:
			addCategory(tree);
			break;
		case 2:
			updateCategory(tree);
			break;
		case 3:
			deleteCategory(tree);
			break;
		case 4:
			searchCategory(tree);
			break;
		case 5:
			CountCategories(tree);
			break;
		case 6:
			getSmallestCategory(tree);
			break;
		case 7:
			getLargestCategory(tree);
			break;
		case 8:
			getHeight(tree);
			break;
		case 9:
			displayAscending(tree);
			break;
		case 10:
			displayPreorder(tree);
			break;
		case 11:
			displayPostorder(tree);
			break;
		case 12:
			displayTree(tree, INDENT);
			break;
		case 13:
			isBalanced(tree);
			break;
		case 14:
			break;
		}
	}
}

void readData(Tree<Category>& tree)
{
	Category item;
	fstream in("Categories.csv");

	if(!in)
	{
		cout << "Couldn't open file" << endl;
		exit(99);
	}

	in >> item.code;
	in.ignore();
	getline(in, item.desc);

	while(!in.eof())
	{
		tree.addItem(item);

		in >> item.code;
		in.ignore();
		getline(in, item.desc);
	}

}

void showMenu(int& choice)
{
	bool isValid = false;


	cout << "Command menu:" << endl
		<< string(41, '=') << endl;
	cout << "1.  Add category" << endl;
	cout << "2.  Update category" << endl;
	cout << "3.  Delete category" << endl;
	cout << "4.  Search for a category" << endl;
	cout << "5.  Display number of nodes in the tree" << endl;
	cout << "6.  Display smallest category" << endl;
	cout << "7.  Display largest category" << endl;
	cout << "8.  Display tree height" << endl;
	cout << "9.  Display categories in ascending order" << endl;
	cout << "10. Display tree in preorder sequence" << endl;
	cout << "11. Display tree in a postorder sequence" << endl;
	cout << "12. Display the tree graphically" << endl;
	cout << "13. Determine AVL status" << endl;
	cout << "14. Quit" << endl;

	cout << endl << "Please enter your choice: ";
	cin >> choice;

	cout << endl << endl;

	while(!isValid)
	{
		if (choice <= 14 && choice >= 1)
		{
			isValid = true;
		}
		else
		{
			cout << "Invalid menu option. Try again: ";
			cin >> choice;

			cout << endl << endl;
		}
	}
}

void addCategory(Tree<Category>& tree)
{
	Category item;

	cout << "Enter Code (Enter '/' when finished): ";
	cin >> item.code;

	if(item.code != '/')
	{
		cout << "Enter description: ";
		cin >> item.desc;
	}
	else
	{
		cout << endl << endl;
	}

	if(isalpha(item.code))
	{
		item.code = toupper(item.code);
	}

	while(item.code != '/')
	{
		if(tree.addItem(item))
		{
			cout << "Category added successfully" << endl << endl;
		}
		else
		{
			cout << "The Category already exists" << endl << endl;
		}

		cout << "Enter Code (Enter '/' when finished): ";
		cin >> item.code;

		if(item.code != '/')
		{
			cout << "Enter description: ";
			cin >> item.desc;
		}
		else
		{
			cout << endl << endl;
		}

		if(isalpha(item.code))
		{
			item.code = toupper(item.code);
		}
	}
}

void updateCategory(Tree<Category>& tree)
{
	Category item;

	cout << "Enter category code to update: ";
	cin >> item.code;
	item.code = toupper(item.code);

	if(tree.searchItem(item))
	{
		cin.ignore();
		cout << "Enter the updated description: ";
		getline(cin, item.desc);
	}

	if(tree.updateList(item))
	{
		cout << "Category successfully updated" << endl << endl; 
	}
	else
	{
		cout << "Category doesn't exist!" << endl << endl;
	}
}

void deleteCategory(Tree<Category>& tree)
{
	Category item;

	cout << "Enter category code to delete: ";
	cin >> item.code;

	item.code = toupper(item.code);

	if(tree.deleteItem(item))
	{
		cout << "Category deleted successfully" << endl << endl;
	}
	else
	{
		cout << "You are trying to delete a non-existing category" << endl << endl;
	}
}

void searchCategory(Tree<Category>& tree)
{
	Category item;

	cout << "Enter category code to search for: ";
	cin >> item.code;
	item.code = toupper(item.code);

	if(tree.searchItem(item))
	{
		cout << "Category found:" << endl;
		cout << item;
	}
	else
	{
		cout << "Category doesn't exist!" << endl << endl;
	}
}

void CountCategories(Tree<Category>& tree)
{
	cout << "Number of Categories: " << tree.getNumOfNodes() << endl << endl;
}

void getSmallestCategory(Tree<Category>& tree)
{
	Category item = tree.getSmallest();

	cout << item;
}

void getLargestCategory(Tree<Category>& tree)
{
	Category item = tree.getLargest();

	cout << item;
}

void getHeight(Tree<Category>& tree)
{
	cout << "Tree height is: " << tree.getHeight() << endl << endl;
}

void displayAscending(Tree<Category>& tree)
{
	tree.displayAscending();
}

void displayPreorder(Tree<Category>& tree)
{
	tree.displayPreorder();
}

void displayPostorder(Tree<Category>& tree)
{
	tree.displayPostorder();
}

void displayTree(Tree<Category>& tree, int indent)
{
	tree.displayTree(indent);
}

void isBalanced(Tree<Category>& tree)
{
	int balance = tree.getTreeBalance();

	if(balance == 1)
	{
		cout << "The tree is left high" << endl << endl;
	}
	else if (balance == -1)
	{
		cout << "The tree is right high" << endl << endl;
	}
	else if(balance == 0)
	{
		cout << "The tree is even" << endl << endl;
	}
}