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
// 탐욕법을 사용할 떄 좋다.

// Spanning Tree
// 1. 모든 노드를 방문할 수 있는 간선들의 집합
// 2. 이 떄 간선의 수는 노드가 N개일 때 N-1개이다. (사이클 포함X)

// Minimum Spanning Tree
// 1. 스패닝 트리
// 2. 모든 간선의 합이 최소한 스패닝 트리
// 3. 사이클을 절대 포함 X

// 탐욕법
// -> 현재 최선의 선택을 했을 때 나중 결과도 최선인 경우

// Kruskal Algorithm 을 이용하여 최소 스패닝 트리 찾기.

class DisJointSet
{
public:
	DisJointSet(int n)
	{
		_parent.resize(n);
		_rank.resize(n, 1);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[vLeader] > _rank[uLeader])
			std::swap(uLeader, vLeader);

		_parent[vLeader] = uLeader;

		if (_rank[uLeader] == _rank[vLeader])
			_rank[uLeader]++;
	}


private:
	vector<int> _parent;
	vector<int> _rank;
};


struct Edge
{
	int vertexU;
	int vertexV;
	int cost;
};

vector<vector<int>> adjacent;
vector<Edge> edges;

void CreateGraph()
{
	//	  0  1  2  3  4  5  6
	// 0  1  1  1  0  0  0  0
	// 1  1  1  0  0  0  0  1
	// 2  1  0  1  1  0  1  0
	// 3  0  0  1  1  0  0  0
	// 4  1  0  0  0  1  0  0
	// 5  0  0  1  0  0  1  0
	// 6  0  1  0  0  0  0  1

	adjacent = vector<vector<int>>(7, vector<int>(7, -1));

	adjacent[0][0] = 0;
	adjacent[0][1] = 4;
	adjacent[0][2] = 1;
	adjacent[0][4] = 8;

	adjacent[1][0] = 4;
	adjacent[1][1] = 0;
	adjacent[1][2] = 2;
	adjacent[1][6] = 7;

	adjacent[2][0] = 1;
	adjacent[2][1] = 2;
	adjacent[2][2] = 0;
	adjacent[2][3] = 4;
	adjacent[2][5] = 5;

	adjacent[3][3] = 0;
	adjacent[3][2] = 4;

	adjacent[4][0] = 8;
	adjacent[4][4] = 0;

	adjacent[5][2] = 5;
	adjacent[5][5] = 0;
	adjacent[5][6] = 80;

	adjacent[6][1] = 7;
	adjacent[6][6] = 0;
	adjacent[6][5] = 80;

	//모든 간선들을 담기
	for (int u = 0; u < adjacent.size(); u++)
	{
		for (int v = 0; v < adjacent[u].size(); v++)
		{
			if (u == v)
				continue;

			if (adjacent[u][v] == -1)
				continue;

			Edge edge;
			edge.vertexU = u;
			edge.vertexV = v;
			edge.cost = adjacent[u][v];
			edges.push_back(edge);

		}
	}
}


vector<Edge> Kruskal()
{
	vector<Edge> result;

	// edges 정렬하기
	std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) -> bool 
		{
			return a.cost < b.cost;
		});

	DisJointSet sets(adjacent.size());

	for (auto edge : edges)
	{
		// 같은 집합이면 다음꺼 보겠다
		if (sets.FindLeader(edge.vertexU) == sets.FindLeader(edge.vertexV))
			continue;

		sets.Merge(edge.vertexU, edge.vertexV);
		result.push_back(edge);
	}

	return result;

}

int main()
{
	CreateGraph();
	auto result = Kruskal();
	

	return 0;
}