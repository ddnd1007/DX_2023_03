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
vector<vector<bool>> adjacent;
vector<bool> visited;


// 인접행렬
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

	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][4] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	adjacent[1][6] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][3] = true;
	adjacent[2][5] = true;

	adjacent[3][3] = true;
	adjacent[3][2] = true;

	adjacent[4][0] = true;
	adjacent[4][4] = true;

	adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][1] = true;
	adjacent[6][6] = true;
}

void DFS(int here)
{
	visited[here] = true;
	cout << here << "를 방문했습니다." << endl;

	for (int there = 0; there < adjacent.size(); there++)
	{
		//본인인지 확인
		if (here == there)
			continue;
		//인접해 있는지 확인
		if (adjacent[here][there] == false)
			continue;
		//방문했는지 확인
		if (visited[there] == true)
			continue;

		DFS(there);
	}

}

int main()
{
	CreateGraph(); // 인접행렬
	visited = vector<bool>(adjacent.size(), false);
	DFS(0);
	
	return 0;
}