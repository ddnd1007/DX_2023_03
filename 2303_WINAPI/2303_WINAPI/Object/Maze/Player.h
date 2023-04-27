#pragma once
class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();

private:
	Vector2 _startPos = {1,1};
	Vector2 _endPos = {1,1};

	int _pathIndex = 0;
	vector<Vector2> _path;

	weak_ptr<Maze> _maze;
};

