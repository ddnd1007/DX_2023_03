<<<<<<< HEAD

=======
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
<<<<<<< HEAD
	Vector2 offset = Vector2(400,100);

=======
	//������
	Vector2 offset = Vector2(400, 100);
	// 2������ Y����� �迭�� ����
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
	_blocks.resize(25);
	for (int y = 0; y < _poolCountY; y++)
	{
		_blocks[y].reserve(25);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<MazeBlock> block = make_shared<MazeBlock>();
<<<<<<< HEAD
			block->SetPostion(offset + Vector2(18 * x, 18 * y));
=======
			block->SetPosition(offset + Vector2(18 * x, 18 * y));
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
			block->SetType(MazeBlock::BlockType::DISABLE);

			_blocks[y].push_back(block);
		}
	}
<<<<<<< HEAD

	CreateMaze();

=======
	CreateMaze();
	// ���� ��ġ ���� �� �� ����
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
	_blocks[_poolCountY - 2][_poolCountX - 2]->SetType(MazeBlock::BlockType::END);
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blockArr : _blocks)
	{
<<<<<<< HEAD
		for(auto block : blockArr)
=======
		for (auto block : blockArr)
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
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

<<<<<<< HEAD
// Maze for Programmer
=======
//Maze for Programmer
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
void Maze::CreateMaze()
{
	// ��� �ձ�
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
<<<<<<< HEAD
			if(x % 2 == 0 || y % 2 == 0)
=======
			if (x % 2 == 0 || y % 2 == 0)
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
				continue;

			_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
<<<<<<< HEAD
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// ������ ������ ó��
			if(x == _poolCountX - 2 && y == _poolCountY - 2)
=======
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// ������ ������ ó��
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
				continue;

			// ������ ���� �� �շ��ְ�
			if (x == _poolCountX - 2)
			{
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// �Ʒ��� ���� �� �շ��ְ�
			if (y == _poolCountY - 2)
			{
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}
<<<<<<< HEAD

			// �Ѱ��� ��� ���� ������ Ȥ�� �Ʒ��� �������� ���� �մ� �۾�
			const int randValue = rand() % 2;
			if(randValue == 0)
=======
			//�Ѱ��� ��� ���� ������ Ȥ�� �Ʒ��� �������� ���� �մ� �۾�
			const int randValue = rand() % 2;
			if (randValue == 0)
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
			else
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}
<<<<<<< HEAD
=======

>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
}
