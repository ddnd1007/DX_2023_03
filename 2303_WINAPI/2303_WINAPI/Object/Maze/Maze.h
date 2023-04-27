<<<<<<< HEAD

=======
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

<<<<<<< HEAD
	Vector2 StartPos() { return {1,1}; }
	Vector2 EndPos() { return Vector2((int)_poolCountX - 2, (int)_poolCountY -2 ); }
=======
	//시작 지점과 끝 지점을 설정
	Vector2 StartPos() { return { 1,1 }; }
	Vector2 EndPos() { return Vector2((int)_poolCountX - 2, (int)_poolCountY - 2 ); }

>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1

	shared_ptr<MazeBlock> Block(int x, int y) { return _blocks[y][x]; }

private:
<<<<<<< HEAD
	UINT _poolCountX = 25;
	UINT _poolCountY = 25;

	vector<vector<shared_ptr<MazeBlock>>> _blocks;
=======
	//25 * 25 배열로 만든다.
	UINT _poolCountX = 25; 
	UINT _poolCountY = 25;
	// 찾기 쉽게 2차원으로 만듦
	vector<vector<shared_ptr<MazeBlock>>> _blocks; 
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
};

