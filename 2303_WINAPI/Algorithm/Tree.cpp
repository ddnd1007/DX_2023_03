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

//tree // list의 진화된 형태
// - root
// - leaf : 자식이 없는 애들 맨 마지막 애들
// - defth

// 1. 계층적 구조를 나타내기에 가장 적합한 구조. ★★
// 2. 서브트리가 존재하며, 트리는 재귀적 속성을 갖는다. ★★

// 완전이진트리 : 벡터로 대체 가능
// 무조건 왼쪽부터 추가됨
// 뺄 때는 오른쪽 부터

struct Node
{
	Node();
	Node(const string& data) : _data(data) {}

	vector<Node*> _children;
	string _data;

};

Node* CreateTree()
{
	Node* root = new Node("개발팀");
	{

		Node* children_1 = new Node("프로그래밍팀");
		root->_children.push_back(children_1);
		{
			{
				Node* children_2 = new Node("서버팀");
				root->_children.push_back(children_2);
			}

			{
				Node* children_2 = new Node("클라이언트팀");
				root->_children.push_back(children_2);
			}

			{
				Node* children_2 = new Node("엔진팀");
				root->_children.push_back(children_2);
			}
		}

		Node* children_1 = new Node("기획");
		root->_children.push_back(children_1);
		{
			{
				Node* children_2 = new Node("스토리");
				root->_children.push_back(children_2);
			}

			{
				Node* children_2 = new Node("레벨디자인");
				root->_children.push_back(children_2);
			}

			{
				Node* children_2 = new Node("밸런스");
				root->_children.push_back(children_2);
			}
		}

		Node* children_1 = new Node("아트팀");
		root->_children.push_back(children_1);
		{
			{
				Node* children_2 = new Node("배경");
				root->_children.push_back(children_2);
			}

			{
				Node* children_2 = new Node("원화");
				root->_children.push_back(children_2);
			}

			{
				Node* children_2 = new Node("모델링");
				root->_children.push_back(children_2);
			}
		}
	}
	return root;
}

void PrintTree(Node* root, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "-";
	}

	cout << root->_data << endl;

	for (auto node : root->_children)
	{
		PrintTree(node, depth + 1);
	}
}

int main()
{

	Node* root = CreateTree();

	PrintTree(root, 0);
	
	return 0;
}