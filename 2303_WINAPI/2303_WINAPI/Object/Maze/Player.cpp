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

	RightHand();
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

	Vector2 frontPos[4] = 
	{
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0} // RIGHT
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
	_discorvered = vector<vector<bool>>(poolCountY, vector<bool>(poolCountX, false));
	_parent = vector<vector<Vector2>>(poolCountY, vector<Vector2>(poolCountX, Vector2(-1,-1)));

	queue<Vector2> q;
	q.push(_startPos);
	_discorvered[_startPos.y][_startPos.x] = true;
	_parent[_startPos.y][_startPos.x] = _startPos;

	while (true)
	{
		if (q.empty() == true)
			break;

		Vector2 here = q.front();
		if (_discorvered[_endPos.y][_endPos.x])
			break;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			Vector2 temp = here + frontPos[i];

			if (_maze.lock()->Block(temp.y, temp.x)->GetType() == MazeBlock::BlockType::DISABLE)
				continue;

			if (_discorvered[temp.y][temp.x] == true)
				continue;


			q.push(temp);
			_discorvered[temp.y][temp.x] = true;
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




bool Player::Cango(Vector2 pos)
{
	Vector2 temp = pos;
	MazeBlock::BlockType type = _maze.lock()->Block(temp.x, temp.y)->GetType();
	if(type == MazeBlock::BlockType::DISABLE)
		return false;
	if (type == MazeBlock::BlockType::NONE)
		return false;

	return true;
}
