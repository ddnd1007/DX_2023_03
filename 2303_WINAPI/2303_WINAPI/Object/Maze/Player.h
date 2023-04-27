#pragma once
class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();

	bool Cango(Vector2 pos);

private:
	Vector2 _startPos = {1,1};
	Vector2 _endPos = {1,1};

	float _time = 0.0f;

	int _pathIndex = 0;
	vector<Vector2> _path;

	weak_ptr<Maze> _maze;
};

