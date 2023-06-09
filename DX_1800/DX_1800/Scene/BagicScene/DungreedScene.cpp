#include "framework.h"
#include "DunGreedScene.h"

#include "../../Object/Obj/DunGreed/DunPlayer.h"

DunGreedScene::DunGreedScene()
{
	_player = make_shared<DunPlayer>();
	_player->SetPosition(CENTER);
}

DunGreedScene::~DunGreedScene()
{
}

void DunGreedScene::Update()
{
	_player->Update();
}

void DunGreedScene::Render()
{
	_player->Render();
}
