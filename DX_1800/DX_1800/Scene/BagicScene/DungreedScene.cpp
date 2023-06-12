#include "framework.h"
#include "DunGreedScene.h"

#include "../../Object/Obj/DunGreed/DunPlayer.h"
#include "../../Object/Obj/DunGreed/DunBullet.h"
#include "../../Object/Obj/DunGreed/DunMonster.h"

DunGreedScene::DunGreedScene()
{
	_player = make_shared<DunPlayer>();
	_player->SetPosition(CENTER);

	for (int i = 0; i < 10; i++)
	{
		_monster = make_shared<DunMonster>();
		_monster->SetPosition(Vector2(rand() % (WIN_WIDTH), rand() % (WIN_HEIGHT)));
	}
}

DunGreedScene::~DunGreedScene()
{
}

void DunGreedScene::Update()
{
	_player->Update();
	for (int i = 0; i < 10; i++)
	{
		if (_monster->IsActive() == false)
			return;

		_monster->Update();
	}

	if (_monster->IsActive() == true)
	{
		for (auto bullet : _player->GetBullets())
		{
			if (bullet->_isActive == false)
				continue;

			if (bullet->GetCollider()->IsCollision(_monster->GetCollider()))
			{
				_monster->TakeDamage(1);
				bullet->_isActive = false;
			}
		}
	}
}

void DunGreedScene::Render()
{
	_player->Render();

	_player->Update();
	for (int i = 0; i < 10; i++)
	{
		if (_monster->IsActive() == false)
			return;

		_monster->Render();
	}
}

void DunGreedScene::PostRender()
{
	ImGui::Text("Monster HP : %d", _monster->_hp);
}
