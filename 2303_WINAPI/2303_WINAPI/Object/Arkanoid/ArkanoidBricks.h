#pragma once
class ArkanoidBricks
{
public:
	ArkanoidBricks();
	~ArkanoidBricks();

	void Update();
	void Render(HDC hdc);
	vector<vector<shared_ptr<ArkanoidBrick>>> GetBricks() { return _arkanoidBricks; }

private:
	vector<vector<shared_ptr<ArkanoidBrick>>> _arkanoidBricks;
	UINT _poolCountX = 10;
	UINT _poolCountY = 6;
};

