#include "framework.h"
#include "MapleScene.h"

#include "../../Object/Maple/MaplePlayer.h"
#include "../../Object/Maple/MapleMonster.h"
#include "../../Object/Maple/MapleArrow.h"
#include "../../Object/Maple/MapleMap.h"
#include "../../Object/Maple/Meso.h"

MapleScene::MapleScene()
{
	_player = make_shared<MaplePlayer>();
	_map = make_shared<MapleMap>();
	_monster = make_shared<MapleMonster>();
	_map->SetPosition(Vector2(0.0f, -350.0f));
	_monster->SetPosition(Vector2(0.0f, -320.0f));
	
	//_meso = make_shared<Meso>();
	//_meso->SetPosition(Vector2(0.0f, -100.0f));


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
	_monster->Update();
	_map->Update();
	//_meso->Update();

	if (_map->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);

	_map->GetCollider()->Block(_monster->GetCirCollider());

	if (_player->GetCollider()->IsCollision(_monster->GetCirCollider()))
	{
		_monster->_isDamaged = true;
		_player->GetCollider()->SetColorRed();
		_monster->GetCirCollider()->SetColorRed();
	}
	else
	{
		_monster->_isDamaged = false;
		_player->GetCollider()->SetColorGreen();
		_monster->GetCirCollider()->SetColorGreen();
		
	}

	if (_player->GetCollider()->IsCollision(_monster->GetRectCollider()))
	{
		
		_player->GetCollider()->SetColorRed();
		_monster->GetRectCollider()->SetColorRed();
	}
	else
	{
		
		_player->GetCollider()->SetColorGreen();
		_monster->GetRectCollider()->SetColorGreen();

	}

	if (_monster->IsActive() == true)
	{
		for (auto arrow : _player->GetBullets())
		{
			if (arrow->_isActive == false)
				continue;

			if (arrow->GetCollider()->IsCollision(_monster->GetCirCollider()))
			{
				_monster->TakeDamage(1);
				_monster->GetCirCollider()->SetColorRed();
				arrow->_isActive = false;
			}
		}
	}
}

void MapleScene::Render()
{
	_map->Render();
	//_meso->Render();
	//_mapleBoss->Render();
	_monster->Render();
	_player->Render();
}

void MapleScene::PostRender()
{
	ImGui::Text("Player HP : %d", _player->_hp);
	ImGui::SliderInt("Player_HP", (int*)&_player->_hp, 0, 10);
	ImGui::Text("Snail HP : %d", _monster->_hp);
}
