#include "framework.h"
#include "ArkanoidBricks.h"

ArkanoidBricks::ArkanoidBricks()
{
	_arkanoidBricks.resize(_poolCountY);
	Vector2 offset = { 400 , 150 };
	for (int y = 0; y < _poolCountY; y++)
	{
		vector<shared_ptr<ArkanoidBrick>> blockX;
		blockX.reserve(_poolCountX);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<ArkanoidBrick> bricks = make_shared<ArkanoidBrick>();
			bricks->SetPosition(offset + Vector2(50 * x, 20 * y));
			bricks->SetType(ArkanoidBrick::ArkanoidBrickType::BRICK);

			_arkanoidBricks[y].push_back(bricks);
			
		}
	}

	
}

ArkanoidBricks::~ArkanoidBricks()
{
}

void ArkanoidBricks::Update()
{
	for (auto brickArr : _arkanoidBricks)
	{
		for (auto brick : brickArr)
			brick->Update();
	}
}

void ArkanoidBricks::Render(HDC hdc)
{
	for (auto brickArr : _arkanoidBricks)
	{
		for (auto brick : brickArr)
			brick->Render(hdc);
	}
}
