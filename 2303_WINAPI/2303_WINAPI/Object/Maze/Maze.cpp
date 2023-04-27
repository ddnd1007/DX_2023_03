#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
	Vector2 offset = Vector2(400,100);

	_blocks.resize(25);
	for (int y = 0; y < _poolCountY; y++)
	{
		_blocks[y].reserve(25);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<MazeBlock> block = make_shared<MazeBlock>();
			block->SetPostion(offset + Vector2(18 * x, 18 * y));
			block->SetType(MazeBlock::BlockType::DISABLE);

			_blocks[y].push_back(block);
		}
	}

	CreateMaze();

	_blocks[_poolCountY - 2][_poolCountX - 2]->SetType(MazeBlock::BlockType::END);
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blockArr : _blocks)
	{
		for(auto block : blockArr)
			block->Update();
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blockArr : _blocks)
	{
		for (auto block : blockArr)
			block->Render(hdc);
	}
}

// Maze for Programmer
void Maze::CreateMaze()
{
	// 노드 뚫기
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// 마지막 도착점 처리
			if(x == _poolCountX - 2 && y == _poolCountY - 2)
				continue;

			// 오른쪽 끝은 다 뚫려있게
			if (x == _poolCountX - 2)
			{
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// 아래쪽 끝은 다 뚫려있게
			if (y == _poolCountY - 2)
			{
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// 한개의 노드 기준 오른쪽 혹은 아래쪽 랜덤으로 길을 뚫는 작업
			const int randValue = rand() % 2;
			if(randValue == 0)
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
			else
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}
}
