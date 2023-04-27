#include "framework.h"
#include "MazeScene.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_player = make_shared<Player>(_maze);
<<<<<<< HEAD
=======

>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_player->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
