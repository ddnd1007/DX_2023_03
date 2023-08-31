#include "framework.h"
#include "MapleBossScene.h"

#include "../../Object/Maple/MaplePlayer.h"
#include "../../Object/Maple/MapleBoss.h"
#include "../../Object/Maple/MapleArrow.h"
#include "../../Object/Maple/MapleBossMap.h"
#include "../../Object/Maple/MaplePortar.h"
#include "../../Object/Maple/Meso.h"

MapleBossScene::MapleBossScene()
{
	_player = make_shared<PlayerManager>();
	_boss = make_shared<MapleBoss>();
	_bossMap = make_shared<MapleBossMap>();

	_boss->SetPosition(Vector2(100, 0));
	_bossMap->SetPosition(Vector2(0.0f, -30.0f));
	_portar = make_shared<MaplePortar>();
	_portar->SetPosition(Vector2(-500.0f, 270.0f));

	/*CAMERA->SetTarget(_player->GetCollider()->GetTransform());
	CAMERA->SetLeftBottom(_bossMap->leftBottom());
	CAMERA->SetRightTop(_bossMap->rightTop());
	CAMERA->SetOffset(Vector2(0, -1010));*/
}

MapleBossScene::~MapleBossScene()
{
}

void MapleBossScene::Update()
{
	_player->Update();
	_boss->Update();
	_bossMap->Update();
	_portar->Update();

	if (_bossMap->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);

	if (_bossMap->GetCollider()->Block(_boss->GetCirCollider()))

		_boss->Hit(_player);

	if (_boss->IsActive() == true)
	{
		if (_boss->GetCirCollider()->IsCollision(_player->GetCollider()))
		{
			_player->TakeDamage(10);
		}
	}

	if (_boss->IsActive() == true)
	{
		for (auto arrow : _player->GetBullets())
		{
			if (arrow->_isActive == false)
				continue;

			if (arrow->GetCollider()->IsCollision(_boss->GetCirCollider()))
			{
				_boss->TakeDamage(1);
				_boss->Hit(_player);
				_boss->GetCirCollider()->SetColorRed();
				arrow->_isActive = false;
			}
		}
	}

	if (_player->GetCollider()->IsCollision(_portar->GetCollider()))
	{
		if (KEY_PRESS('W'))
		{
			SCENE->PrevScene();
		}
	}
}



void MapleBossScene::Render()
{
	_bossMap->Render();
	_portar->Render();
	//_meso->Render();
	_boss->Render();
	_player->Render();
}

void MapleBossScene::PostRender()
{
	ImGui::SliderInt("Player_HP", (int*)&_player->GetHp(), 0, 100);
	
	//ImGui::Text("Snail HP : %d", _monster[i]->_hp);
	ImGui::SliderInt("Boss_HP", (int*)&_boss->_hp, 0, 200);
	
}
