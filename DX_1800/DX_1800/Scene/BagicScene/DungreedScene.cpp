#include "framework.h"
#include "DunGreedScene.h"

#include "../../Object/Obj/DunGreed/DunPlayer.h"
#include "../../Object/Obj/DunGreed/DunBullet.h"
#include "../../Object/Obj/DunGreed/DunMonster.h"

DunGreedScene::DunGreedScene()
{
	_player = make_shared<DunPlayer>();
	_player->SetPosition(CENTER + Vector2(-200.0f, 0.0f));

	for (int i = 0; i < 10; i++)
	{
		shared_ptr<DunMonster> monster = make_shared<DunMonster>();

		float xPos = rand() % WIN_WIDTH;
		float yPos = rand() % WIN_HEIGHT;

		monster->GetTransform()->SetPosition(Vector2(xPos, yPos));
		_monsters.push_back(monster);
	}
}

DunGreedScene::~DunGreedScene()
{
}

void DunGreedScene::Update()
{
	_player->Update();

	for (auto monster : _monsters)
	{
		monster->Update();
		monster->SetDir(_player->GetTransform()->GetWorldPos());
		_player->GetCollider()->Block(monster->GetCollider());
		for (auto bullet : _player->GetBullets())
		{
			bullet->Attack(monster);
		}

		for (auto bible : _player->GetBibles())
		{
			if (bible->IsCollision(monster->GetCollider()))
			{
				if (monster->IsDamaged() == false)
				{
					Vector2 temp = monster->GetTransform()->GetWorldPos() - _player->GetTransform()->GetWorldPos();
					temp.Normalize();
					monster->GetTransform()->AddVector2(temp * 20.0f);
					monster->TakeDamage(1);
				}
			}
		}
	}

}

void DunGreedScene::Render()
{
	_player->Render();
	for (auto monster : _monsters)
	{
		monster->Render();
	}
}

void DunGreedScene::PostRender()
{
	for (int i = 0; i < _monsters.size(); i++)
	{
		ImGui::Text("Monster%d HP : %d", i + 1, _monsters[i]->GetHp());
	}
}
