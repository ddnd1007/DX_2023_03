#pragma once
class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();

<<<<<<< HEAD
	bool Cango(Vector2 pos);
=======
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1

private:
	Vector2 _startPos = {1,1};
	Vector2 _endPos = {1,1};
<<<<<<< HEAD

	float _time = 0.0f;

=======
	
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
	int _pathIndex = 0;
	vector<Vector2> _path;

	weak_ptr<Maze> _maze;
};

