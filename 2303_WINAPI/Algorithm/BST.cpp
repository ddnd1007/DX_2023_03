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
		return nullptr;

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

	/*while (true)
	{
		if (node == nullptr)
			break;

		if (node->left != nullptr)
		{
			Min(node->left);
			break;
		}
	}
	return node;*/
}

Node* BST::Max(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->right != nullptr)
		return Max(node->right);

	return node;
}

Node* BST::Previous(Node* node)
{
	//Node* current = Search(node, key);
	//if (current == nullptr) 
	//{
	//	return nullptr;
	//}

	//if (current->left != nullptr)
	//{
	//	Node* temp = current->left;
	//	while (temp->right != nullptr) 
	//	{
	//		temp = temp->right;
	//	}
	//	return temp;
	//}
	//else 
	//{
	//	Node* parent = nullptr;
	//	Node* root = node;
	//	while (root != current)
	//	{
	//		if (current->key > root->key)
	//		{
	//			parent = root;
	//			root = root->right;
	//		}
	//		else
	//		{
	//			root = root->left;
	//		}
	//	}
	//	return parent;
	//}

	if (node == nullptr)
		return nullptr;

	if (node->left == nullptr)
		return nullptr;

	return Max(node->left);
}


Node* BST::Next(Node* node)
{
	/*Node* current = Search(node, key);
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
	}*/
	if (node == nullptr)
		return nullptr;

	if (node->right == nullptr)
		return nullptr;

	return Min(node->right);
}

void BST::Delete(Node* node)
{
	if (node == nullptr)
		return;
	// 지울 노드에 왼쪽 자식이 없다.
	if (node->left == nullptr)
		Replace(node, node->right);
	// 지울 노드에 오른쪽 자식이 없다.
	else if (node->right == nullptr)
		Replace(node, node->left);
	//자식 둘다 있는 경우
	else
	{
		Node* prev = Previous(node);
		node->key = prev->key;
		node->data = prev->data;
		Delete(prev);
	}

}

void BST::Replace(Node* node1, Node* node2)
{
	// node1이 루트일 때
	if (node1->parent == nullptr)
		_root = node2;

	// node1이 부모쪽에서 왼쪽 자식  노드일 때
	else if (node1 == node1->parent->left)
	{
		node1->parent->left = node2;
	}
	// node1이 부모쪽에서 오른쪽 자식 노드일 때
	else if (node1 == node1->parent->right)
	{
		node1->parent->right = node2;
	}

	if (node2 != nullptr)
		node2->parent = node1->parent;

	delete node1;
}
