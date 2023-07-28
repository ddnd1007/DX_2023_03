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
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<MapleMonster> monster = make_shared<MapleMonster>();
		int randomX = monster->getRandomNumber(0, WIN_WIDTH - 700);
		monster->SetPosition(Vector2(randomX, -330));
		_monster.push_back(monster);
	}
	_map->SetPosition(Vector2(0.0f, -350.0f));
	
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
	if (_map->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);

	for (auto monster : _monster)
		monster->Update();
	
	for (int i = 0; i < 5; i++)
	{
		_map->GetCollider()->Block(_monster[i]->GetCirCollider());
	}

	for (int i = 0; i < 5; i++)
	{
		if (_player->GetCollider()->IsCollision(_monster[i]->GetCirCollider()))
		{
			_monster[i]->_isDamaged = true;
			_player->GetCollider()->SetColorRed();
			_monster[i]->GetCirCollider()->SetColorRed();
		}
		else
		{
			_monster[i]->_isDamaged = false;
			_player->GetCollider()->SetColorGreen();
			_monster[i]->GetCirCollider()->SetColorGreen();

		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (_player->GetCollider()->IsCollision(_monster[i]->GetRectCollider()))
		{
		
			_player->GetCollider()->SetColorRed();
			_monster[i]->GetRectCollider()->SetColorRed();
		}
		else
		{
		
			_player->GetCollider()->SetColorGreen();
			_monster[i]->GetRectCollider()->SetColorGreen();

		}
	}

	for (int i = 0; i < 5; i++)
	{
		

		if (_monster[i]->IsActive() == true)
		{
			if (_monster[i]->GetCirCollider()->IsCollision(_player->GetCollider()))
			{
				
				_player->TakeDamage(3);
				//_player->_isDamaged == false;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (_monster[i]->IsActive() == true)
		{
			for (auto arrow : _player->GetBullets())
			{
				if (arrow->_isActive == false)
					continue;

				if (arrow->GetCollider()->IsCollision(_monster[i]->GetCirCollider()))
				{
					_monster[i]->TakeDamage(1);
					_monster[i]->GetCirCollider()->SetColorRed();
					arrow->_isActive = false;
				}
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (_monster[i]->IsActive() == false)
			return;

		if (_player->IsActive() == false)
			return;
		
		if (_monster[i]->GetRectCollider()->IsCollision(_player->GetCollider()))
		{
			_monster[i]->Move(_player);
		}
	}
}

void MapleScene::Render()
{
	_map->Render();
	//_meso->Render();
	//_mapleBoss->Render();
	for (auto monster : _monster)
		monster->Render();

	_player->Render();
}

void MapleScene::PostRender()
{
	//ImGui::Text("Player HP : %d", _player->GetHp());
	ImGui::SliderInt("Player_HP", (int*)&_player->GetHp(), 0, 100);
	for (int i = 0; i < 5; i++)
	{
		//ImGui::Text("Snail HP : %d", _monster[i]->_hp);
		ImGui::SliderInt("Snail_HP", (int*)&_monster[i]->_hp, 0, 3);
	}
}
