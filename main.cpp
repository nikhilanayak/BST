// Binary Search Tree implementation in C++
// Include Node and C++ std libraries
#include "Node.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <cstring>

bool search(Node *curr, int num, Node *&newPtr) // cehck if number exists in BST
{
	if (curr->data == num)
	{
		newPtr = curr;
		return true;
	}
	if (curr->data > num && curr->left != NULL)
	{
		return search(curr->left, num, newPtr);
	}
	if (curr->data < num && curr->right != NULL)
	{
		return search(curr->right, num, newPtr);
	}
	return false;
}

void remove(Node *&root, Node *curr, int num, Node *newPtr)
{  // remove number from BST, covers all edge cases
	if (search(curr, num, newPtr) == true)
	{  // if the number exists. Don't delete if it doesn't exist
		Node *tmp = newPtr;
		if (tmp == root)
		{  // if root is deleted
			if (tmp->left == NULL && tmp->right == NULL)
			{ // no children
				root = NULL;
				newPtr = NULL;
			}
			else if (tmp->left != NULL && tmp->right == NULL)
			{  // left child
				root = root->left;
				newPtr = NULL;
			}
			else if (tmp->left == NULL && tmp->right != NULL)
			{  // right child
				root = root->right;
				newPtr = NULL;
			}
			else
			{  // two children
				Node *newNode = tmp->right;
				while (newNode->left != NULL)
				{
					newNode = newNode->left;
				}
				tmp->data = newNode->data;
				if (newNode == tmp->right)
				{
					tmp->right = tmp->right->right;
				}
				newPtr = NULL;
			}
		}
		else
		{ // not root node
			if (tmp->left == NULL && tmp->right == NULL)
			{ // no children
				if (tmp->parent->left == tmp)
				{ // left child
					tmp->parent->left = NULL;
					delete tmp;
				}
				else
				{ // right child
					tmp->parent->right = NULL;
					delete tmp;
				}
				newPtr = NULL;
			}
			else if (tmp->left != NULL && tmp->right == NULL)
			{ // tmp only has right child
				Node *tmpParent = tmp->parent;
				if (tmpParent->left == tmp)
				{ // if it's a left leaf
					tmpParent->left = tmp->left;
					tmp->left->parent = tmpParent;
				}
				else
				{ // if it's a right leaf
					tmpParent->right = tmp->left;
					tmp->left->parent = tmpParent;
				}
				delete tmp; // Deletes temp
				newPtr = NULL;
			}
			else if (tmp->left == NULL && tmp->right != NULL)
			{ //only has a right child
				Node *tempParent = tmp->parent;
				if (tempParent->left == tmp)
				{ // if it is a left chlid
					tempParent->left = tmp->right;
					tmp->right->parent = tempParent;
				}
				else
				{ // if right child
					tempParent->right = tmp->right;
					tmp->right->parent = tempParent;
				}
				delete tmp;
				newPtr = NULL;
			}
			else
			{ // 2 children
				Node *newNode = tmp->right;
				while (newNode->left != NULL)
				{
					newNode = newNode->left;
				}
				tmp->data = newNode->data;
				if (newNode == tmp->right)
				{
					tmp->right = tmp->right->right;
				}
			}
		}
	}
}

void recursiveAdd(Node *curr, int value)
{ // adds a number to the BST by recursively going through the tree
	if (curr->data >= value && curr->left == NULL)
	{
		curr->setLeft(new Node(value));
		curr->left->parent = curr;
	}
	else if (curr->data < value && curr->right == NULL)
	{
		curr->setRight(new Node(value));
		curr->right->parent = curr;
	}
	else if (curr->data >= value)
	{
		recursiveAdd(curr->left, value);
	}
	else if (curr->data < value)
	{
		recursiveAdd(curr->right, value);
	}
}

void display(Node* n, int depth){ // recursively prints a BST
	if(n->right != NULL){
		display(n->right, depth + 1);
	}
	for(int i = 0; i < depth; i++){
		std::cout << "\t";
	}
	std::cout << n->data << "\n";
	if(n->left != NULL){
		display(n->left, depth + 1);
	}
}

void upload(Node *&root)
{ // gets numbers from numbers.txt and adds them to BST
	std::cout << "How many numbers: ";
	int input;
	std::cin >> input;

	for (int i = 0; i < input; i++)
	{
		char input[10];
		char tmp[10];
		int count = 1;
		int num;
		int random = (rand() % 50) + 1;
		std::fstream file("numbers.txt");

		while (file.getline(input, 10, ' '))
		{
			if (count == random)
			{
				strcpy(tmp, input);
				count++;
			}
			count++;
		}
		num = atoi(tmp);

		if (root == NULL)
		{
			root = new Node(num);
			root->parent = NULL;
		}
		else if (root != NULL)
		{
			recursiveAdd(root, num);
		}
	}
}

void add(Node*& root){ // add nunber to BST just like upload, but manually
	std::cout << "Enter a number to add: ";
	int num;
	std::cin >> num;
	if(root == NULL){
		root = new Node(num);
		root->parent = NULL;
		return;
	}
	recursiveAdd(root, num);
}

int main()
{
	srand(time(0)); // random seed

	Node *root = NULL;
	Node *newPtr = NULL;

	while (true) // loop
	{
		std::cout << "U=Upload File, A=Add, S=Search, D=Display, R=Remove, Q=Quit: ";
		char input[256];
		std::cin >> input;
		switch (input[0]) // check first character to see what input was
		{
		case 'U':
		{
			upload(root);
			break;
		};

		case 'A':
		{
			add(root);
			break;
		};
		case 'S':
		{
			std::cout << "What would you like to search for: ";
			int tosearch;
			std::cin >> tosearch;
			bool found = search(root, tosearch, newPtr);
			if(found){
				std::cout << "Found!";
			}
			else{
				std::cout << "Not Found.";
			}
			break;
		};
		case 'D':
		{
			display(root, 0);
			break;
		};

		case 'R':
		{
			std::cout << "What would you like to remove: ";
			int toremove;
			std::cin >> toremove;
			remove(root, root, toremove, newPtr);
			break;
		};

		case 'Q':
		{
			exit(0);
		};
		}
	}
}
