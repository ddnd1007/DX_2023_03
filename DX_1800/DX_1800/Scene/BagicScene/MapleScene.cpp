#include "framework.h"
#include "MapleScene.h"

#include "../../Object/Maple/MaplePlayer.h"
#include "../../Object/Maple/MapleMap.h"
#include "../../Object/Maple/Meso.h"

MapleScene::MapleScene()
{
	_player = make_shared<MaplePlayer>();
	_map = make_shared<MapleMap>();
	_map->SetPosition(Vector2(0.0f, -350.0f));
	_meso = make_shared<Meso>();
	_meso->SetPosition(Vector2(0.0f, -100.0f));


	CAMERA->SetTarget(_player->GetCollider()->GetTransform());
	CAMERA->SetLeftBottom(_map->leftBottom());
	CAMERA->SetRightTop(_map->rightTop());
	CAMERA->SetOffset(Vector2(0, -80));
	
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_player->Update();
	
	_map->Update();
	_meso->Update();

	if (_map->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);
	
}

void MapleScene::Render()
{
	_map->Render();
	_meso->Render();
	//_mapleBoss->Render();
	_player->Render();
}

void MapleScene::PostRender()
{
	ImGui::Text("Player HP : %d", _player->_hp);
}