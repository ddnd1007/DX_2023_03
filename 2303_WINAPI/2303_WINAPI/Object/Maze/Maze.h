#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	struct Edge
	{
		Vector2 u;
		Vector2 v;
		int cost;
	};

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	void CreateMaze_Kruskal();

	Vector2 StartPos() { return {1,1}; }
	Vector2 EndPos() { return Vector2((int)_poolCountX - 2, (int)_poolCountY -2 ); }

	shared_ptr<MazeBlock> Block(int x, int y) { return _blocks[y][x]; }

	Vector2 PoolCount() { return Vector2((int)_poolCountX,(int)_poolCountY); }

private:
	UINT _poolCountX = 25;
	UINT _poolCountY = 25;

	vector<vector<shared_ptr<MazeBlock>>> _blocks;

	// Kruskal
	vector<Edge> edges;
};

