#include "framework.h"
#include "DungreedScene.h"

DungreedScene::DungreedScene()
{
	
	_player = make_shared<DunPlayer>();

}

DungreedScene::~DungreedScene()
{
}


void DungreedScene::Update()
{
	_player->Update();
}

void DungreedScene::Render()
{
	_player->Render();
}

