#include "framework.h"
#include "DunGreedScene.h"

#include "../../Object/Obj/DunGreed/DunPlayer.h"
#include "../../Object/Obj/DunGreed/DunBoss.h"


DunGreedScene::DunGreedScene()
{
	_player = make_shared<DunPlayer>();
	_boss = make_shared<DunBoss>();

}

DunGreedScene::~DunGreedScene()
{
}

void DunGreedScene::Collider_Update()
{
	
}

void DunGreedScene::Update()
{
	_player->Update();
	_boss->Update();
}

void DunGreedScene::Render()
{
	_player->Render();
	_boss->Render();
}
