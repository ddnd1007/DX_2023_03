#include <iostream>

using namespace std;

#include "BST.h"

BST::BST()
{
}

BST::~BST()
{
}

void BST::Insert(int key)
{
	Node* newNode = new Node(key);

	//트리의 첫 생성
	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;

		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	node = newNode;
	node->parent = parent;
	
	if (node->key < parent->key)
		parent->left = node;
	else
		parent->right = node;
}
	

void BST::PrintTree(Node* node)
{
	if (node == nullptr)
		return;

	PrintTree(node->left);
	cout << node->key << endl;
	PrintTree(node->right);
}

Node* BST::Search(Node* node, int key)
{
	if (node == nullptr)
		return node;

	if (node->key == key)
		return node;

	if (key < node->key)
		return  Search(node->left, key);
	else
		return  Search(node->right, key);

	return nullptr;
}

Node* BST::Min(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->left != nullptr)
		return Min(node->left);

	return node;
}

Node* BST::Max(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->left != nullptr)
		return Max(node->right);

	return node;
}

Node* BST::Previous(Node* node, int key)
{
	Node* current = Search(node, key);
	if (current == nullptr) {
		return nullptr;
	}

	if (current->left != nullptr) {
		Node* temp = current->left;
		while (temp->right != nullptr) {
			temp = temp->right;
		}
		return temp;
	}
	else {
		Node* parent = nullptr;
		Node* root = node;
		while (root != current) {
			if (current->key > root->key) {
				parent = root;
				root = root->right;
			}
			else {
				root = root->left;
			}
		}
		return parent;
	}
}


Node* BST::Next(Node* node, int key)
{
	Node* current = Search(node, key);
	if (current == nullptr)
	{
		return nullptr;
	}

	if (current->right != nullptr)
	{
		Node* temp = current->right;
		while (temp->left != nullptr) 
		{
			temp = temp->left;
		}
		return temp;
	}
	else 
	{
		Node* parent = nullptr;
		Node* root = node;
		while (root != current) {
			if (current->key < root->key)
			{
				parent = root;
				root = root->left;
			}
			else 
			{
				root = root->right;
			}
		}
		return parent;
	}
}
