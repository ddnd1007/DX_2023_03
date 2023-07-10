#include "framework.h"
#include "MapleScene.h"

#include "../../Object/Maple/MaplePlayer.h"
#include "../../Object/Maple/MapleMap.h"

MapleScene::MapleScene()
{
	_player = make_shared<MaplePlayer>();
	_map = make_shared<MapleMap>();
	_map->SetPosition(Vector2(0.0f, -350.0f));

	CAMERA->SetTarget(_player->GetCollider()->GetTransform());
	CAMERA->SetLeftBottom(_map->leftBottom());
	CAMERA->SetRightTop(_map->rightTop());
	
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_player->Update();
	
	_map->Update();

	if (_map->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);
	
}

void MapleScene::Render()
{
	_map->Render();
	//_mapleBoss->Render();
	_player->Render();
}

void MapleScene::PostRender()
{
}
