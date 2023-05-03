#pragma once
class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	void BFS();
	void DFS();
	void DFS(Vector2 here);
	void Dijkstra(Vector2 startIndex);

	bool Cango(Vector2 pos);

	struct Vertex
	{
		int _vertexNum;
		int _cost;

		bool operator<(const Vertex& other) const
		{
			return _cost < other._cost;
		}

		bool operator>(const Vertex& other) const
		{
			return _cost > other._cost;
		}
	};

private:
	Vector2 _startPos = { 1,1 };
	Vector2 _endPos = { 1,1 };

	float _time = 0.0f;

	int _pathIndex = 0;
	int _visitedIndex = 0;


	
	vector<Vector2> _path;
	vector<Vector2> _visited;

	weak_ptr<Maze> _maze;

	vector<vector<bool>> _discovered;
	vector<vector<Vector2>> _parent;
	vector<vector<int>> _best;

};

