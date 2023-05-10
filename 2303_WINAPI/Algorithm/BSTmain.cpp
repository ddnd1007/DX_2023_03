#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

#include "BST.h"

// BST (Binary Search Tree) => ���� Ž�� Ʈ��

int main()
{
	BST bst;
	bst.Insert(15);
	bst.Insert(7);
	bst.Insert(30);
	bst.Insert(3);
	bst.Insert(10);
	bst.Insert(25);

	
	//bst.PrintTree(bst._root);
	
	Node* newRoot = bst.Search(bst._root, 7);
	Node* nextRoot = bst.Next(bst._root);
	Node* prevRoot = bst.Previous(bst._root);
	Node* minRoot = bst.Min(bst._root);

	return 0;
}