#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

	//시작 지점과 끝 지점을 설정
	Vector2 StartPos() { return { 1,1 }; }
	Vector2 EndPos() { return Vector2((int)_poolCountX - 2, (int)_poolCountY - 2 ); }


	shared_ptr<MazeBlock> Block(int x, int y) { return _blocks[y][x]; }

private:
	//25 * 25 배열로 만든다.
	UINT _poolCountX = 25; 
	UINT _poolCountY = 25;
	// 찾기 쉽게 2차원으로 만듦
	vector<vector<shared_ptr<MazeBlock>>> _blocks; 
};

