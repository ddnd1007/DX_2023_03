#include "framework.h"
#include "Player.h"
#include <stack>
#include <queue>



Player::Player(shared_ptr<Maze> maze)
: _maze(maze)
{
	if (_maze.expired() == false)
	{
		_startPos = _maze.lock()->StartPos();
		_endPos = _maze.lock()->EndPos();
		_maze.lock()->Block(_startPos.x, _startPos.y)->SetType(MazeBlock::BlockType::PLAYER);
	}

	Astar();
}

Player::~Player()
{
}

void Player::Update()
{
	_time += 0.4f;
	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pathIndex++;
	}

	if (_pathIndex >= _path.size())
	{
		_pathIndex = 0;
		_path.clear();

		_maze.lock()-> CreateMaze_Kruskal();

		Astar();

		return;
	}

	Vector2 temp = _path[_pathIndex];

	if (_pathIndex > 1)
	{
		Vector2 footPrint = _path[_pathIndex - 1];
		_maze.lock()->Block(footPrint.x, footPrint.y)->SetType(MazeBlock::BlockType::FOOTPRINT);
	}

	_maze.lock()->Block(temp.x, temp.y)->SetType(MazeBlock::BlockType::PLAYER);
}

void Player::RightHand()
{
	Vector2 pos = _startPos;
	_path.push_back(pos);
	Dir curDir = Dir::DIR_UP;

	Vector2 frontPos[8] = 
	{
		Vector2 {1, 1}, // DOWNRIGHT
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {1,-1}, // UPRIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1,-1}, // DOWNLEFT
		Vector2 {-1, 1},// UPLEFT
		Vector2 {-1, 0}, // LEFT
		
	};

	while (true)
	{
		if(pos == _endPos)
			break;

		int newDir = (curDir - 1 + Dir::DIR_COUNT) % Dir::DIR_COUNT;
		Vector2 oldDirVector = frontPos[curDir]; // 기존방향벡터
		Vector2 newDirVector = frontPos[newDir]; // 새로운방향벡터(시계방향)

		// 현재 바라는방향에서 오른쪽 손을 짚었을 때 갈 수 있는 곳인지 확인
		if (Cango(pos + newDirVector))
		{
			curDir = static_cast<Dir>(newDir);
			pos += newDirVector;
			_maze.lock()->Block(pos.x, pos.y)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}

		// 현재 바라보는 방향으로 전진할 수 있는지 확인
		else if (Cango(pos + oldDirVector))
		{
			pos += oldDirVector;
			_maze.lock()->Block(pos.x, pos.y)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}

		// 오른쪽 손 짚어도 못가고, 앞으로도 못가는 상황 반시계로 회전
		else
		{
			curDir = static_cast<Dir>((curDir + 1 + Dir::DIR_COUNT) % Dir::DIR_COUNT);
		}
	}

	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
			s.push(_path[i]);
	}

	s.push(_endPos);

	_path.clear();

	while (true)
	{
		if(s.empty())
			break;
		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());

	return;
}

void Player::BFS()
{
	Vector2 frontPos[4] =
	{
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0} // RIGHT
	};

	Vector2 startPos = _maze.lock()->StartPos();
	Vector2 endPos = _maze.lock()->EndPos();

	Vector2 poolCount = _maze.lock()->PoolCount();
	int poolCountX = (int)poolCount.x;
	int poolCountY = (int)poolCount.y;
	_discovered = vector<vector<bool>>(poolCountY, vector<bool>(poolCountX, false));
	_parent = vector<vector<Vector2>>(poolCountY, vector<Vector2>(poolCountX, Vector2(-1,-1)));

	queue<Vector2> q;
	q.push(_startPos);
	_discovered[_startPos.y][_startPos.x] = true;
	_parent[_startPos.y][_startPos.x] = _startPos;

	while (true)
	{
		if (q.empty() == true)
			break;

		Vector2 here = q.front();
		if (_discovered[_endPos.y][_endPos.x])
			break;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			Vector2 temp = here + frontPos[i];

			if (_maze.lock()->Block(temp.y, temp.x)->GetType() == MazeBlock::BlockType::DISABLE)
				continue;

			if (_discovered[temp.y][temp.x] == true)
				continue;


			q.push(temp);
			_discovered[temp.y][temp.x] = true;
			_parent[temp.y][temp.x] = here;

			_maze.lock()->Block(temp.y, temp.x)->SetType(MazeBlock::BlockType::VISITED);
		}
		
	}

	Vector2 pos = endPos;
	_path.push_back(endPos);
	_path.push_back(endPos);
	while (true)
	{
		if (pos == startPos)
			break;

		pos = _parent[pos.y][pos.x];
		_path.push_back(pos);
	}
	std::reverse(_path.begin(), _path.end()); 
	

	
}

void Player::DFS()
{

	Vector2 poolCount = _maze.lock()->PoolCount();
	int poolCountX = (int)poolCount.x;
	int poolCountY = (int)poolCount.y;
	_discovered = vector<vector<bool>>(poolCountY, vector<bool>(poolCountX, false));

	_discovered[_startPos.y][_startPos.x] = true;
	_visited.push_back(_startPos);

	DFS(_startPos);

	std::reverse(_path.begin(), _path.end());
}

void Player::DFS(Vector2 here)
{
	Vector2 frontPos[4] =
	{
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0} // RIGHT
	};

	_discovered[here.y][here.x] = true;
	_visited.push_back(here);

	for (int i = 0; i < 4; i++)
	{
		Vector2 there = here + frontPos[i];
		if (here == there)
			continue;
		if (Cango(there) == false)
			continue;
		if (_discovered[there.y][there.x] == true)
			continue;
		if (_visited.back() == _endPos)
			break;

		DFS(there);
	}

	if (_visited.back() == _endPos)
	{
		_path.push_back(here);
	}
}

void Player::Dijkstra()
{
	struct Vertex
	{
		Vector2 vertexVector;
		int cost;

		bool operator<(const Vertex& other) const
		{
			return cost < other.cost;
		}

		bool operator>(const Vertex& other) const
		{
			return cost > other.cost;
		}
	};

	Vector2 frontPos[8] =
	{
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT
		Vector2 {1, 1}, // DOWNRIGHT
		Vector2 {1,-1}, // UPRIGHT
		Vector2 {-1,-1}, // DOWNLEFT
		Vector2 {-1, 1},// UPLEFT

	};

	int Dijkstra_Dij[8]
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14,
	};

	Vector2 poolCount = _maze.lock()->PoolCount();
	int poolCountX = (int)poolCount.x;
	int poolCountY = (int)poolCount.y;

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	vector<vector<int>> _best = vector<vector<int>>(poolCountY, vector<int>(poolCountX, INT_MAX));
	_parent = vector<vector<Vector2>>(poolCountY, vector<Vector2>(poolCountX, Vector2(-1, -1)));

	Vertex start;
	start.vertexVector = _startPos;
	start.cost = 0;

	pq.push(start);
	_best[start.vertexVector.y][start.vertexVector.x] = start.cost;
	_parent[start.vertexVector.y][start.vertexVector.x] = start.vertexVector;

	while (true)
	{
		if (pq.empty())
			break;

		int cost = pq.top().cost;
		Vector2 here = pq.top().vertexVector;
		pq.pop();
		

		if (here == _endPos)
			break;

		if (_best[here.y][here.x] < cost)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if (here == there)
				continue;

			if (Cango(there) == false)
				continue;

			int nextCost = _best[here.y][here.x] + Dijkstra_Dij[i];

			if (nextCost >= _best[there.y][there.x])
				continue;
			
			
			Vertex v;
			v.vertexVector = there;
			v.cost = nextCost;
			pq.push(v);
			_best[there.y][there.x] = nextCost;
			_parent[there.y][there.x] = here;
		}
	}

	Vector2 pos = _endPos;
	_path.push_back(_endPos);
	_path.push_back(_endPos);
	while (true)
	{
		if (pos == _startPos)
			break;

		pos = _parent[pos.y][pos.x];
		_path.push_back(pos);
	}
	std::reverse(_path.begin(), _path.end());;
}

void Player::Astar()
{
	Vector2 frontPos[8] =
	{
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT
		Vector2 {1, 1}, // DOWNRIGHT
		Vector2 {1,-1}, // UPRIGHT
		Vector2 {-1,-1}, // DOWNLEFT
		Vector2 {-1, 1},// UPLEFT
	};

	int weights[8] = {10,10,10,10,14,14,14,14};

	Vector2 poolCount = _maze.lock()->PoolCount();
	int poolCountX = (int)poolCount.x;
	int poolCountY = (int)poolCount.y;
	_discovered = vector<vector<bool>>(poolCountY, vector<bool>(poolCountX, false));
	_parent = vector<vector<Vector2>>(poolCountY, vector<Vector2>(poolCountX, Vector2(-1, -1)));
	_best = vector<vector<int>>(poolCountY, vector<int>(poolCountX, INT_MAX));

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	Vertex startV;
	startV.pos = _startPos;
	startV.g = 0; //cost
	startV.h = _startPos.ManhattenDistance(_endPos) * 10;
	startV.f = startV.g + startV.h;

	pq.push(startV);
	_discovered[_startPos.y][_startPos.x] = true;
	_parent[_startPos.y][_startPos.x] = _startPos;
	_best[_startPos.y][_startPos.y] - startV.f;

	while (true)
	{
		if (pq.empty())
			break;

		Vertex hereV = pq.top();
		int hereG = hereV.g;
		int hereH = hereV.h;
		int hereF = hereV.f;
		pq.pop();

		if (_best[hereV.pos.y][hereV.pos.x] < hereF)
			continue;

		if (hereV.pos == _endPos)
			break;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = hereV.pos + frontPos[i];

			if (hereV.pos == there)
				continue;

			if (!Cango(there))
				continue;

			int newG = hereG + weights[i];
			int newH = there.ManhattenDistance(_endPos) * 10;
			int newF = newG + newH;

			if (_best[there.y][there.x] < newF)
				continue;

			Vertex thereV;
			thereV.pos = there;
			thereV.g = newG;
			thereV.h = newH;
			thereV.f = newF;


			pq.push(thereV);
			_best[there.y][there.x] = newF;
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = hereV.pos;
			_maze.lock()->Block(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}
	
	Vector2 pos = _endPos;
	_path.push_back(pos);

	while (true)
	{
		if (pos == _startPos)
			break;
		pos = _parent[pos.y][pos.x];
		_path.push_back(pos);
	}

	std::reverse(_path.begin(), _path.end());
}


bool Player::Cango(Vector2 pos)
{
	Vector2 temp = pos;
	MazeBlock::BlockType type = _maze.lock()->Block(temp.x, temp.y)->GetType();
	if (type == MazeBlock::BlockType::DISABLE)
		return false;
	if (type == MazeBlock::BlockType::NONE)
		return false;

	return true;
}
