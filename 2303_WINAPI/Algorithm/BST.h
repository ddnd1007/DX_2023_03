#pragma once

struct Node
{
	Node() {}
	Node(int key) : key(key) {}

	int key = -1;
	int data = 0;

	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};
class BST
{
public:
	BST();
	~BST();

	void Insert(int key);
	void PrintTree(Node* node);

	Node* Search(Node* node, int key);
	Node* Min(Node* node);
	Node* Max(Node* node);

	Node* Previous(Node* node, int key);
	Node* Next(Node* node, int key);

public:
	Node* _root = nullptr;
};

