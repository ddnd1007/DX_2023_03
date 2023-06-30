#include "framework.h"
#include "MapleScene.h"

#include "../../Object/Maple/MapleBoss.h"

MapleScene::MapleScene()
{
	_mapleBoss = make_shared<MapleBoss>();
	_mapleBoss->SetPosition(Vector2(0, 0));
	
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_mapleBoss->Update();
}

void MapleScene::Render()
{
	_mapleBoss->Render();
}

void MapleScene::PostRender()
{
}
