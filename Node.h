// Used to represent one node in a Binary Search Tree. Stores data and relationship with other nodes.
#ifndef NODE_H
#define NODE_H

class Node{
public:
	Node *left, *right, *parent; //  other nodes
	int data; // this node's data
	Node(int data){
		this->data = data;
	}

	// setters
	void setLeft(Node* left){ 
		this->left = left;
	}
	void setRight(Node* right){
		this->right = right;
	}

	// getters
	int getData(){ return data; } 
	Node* getLeft(){ return left; } 
	Node* getRight(){ return right; } 
	Node* getParent(){ return parent; } 

};

#endif
