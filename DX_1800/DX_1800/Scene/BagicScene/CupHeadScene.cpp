#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/Obj/CupHead/CupHead.h"
#include "../../Object/Obj/CupHead/CupBG.h"
#include "../../Object/Obj/CupHead/CupMonster.h"
#include "../../Object/Obj/CupHead/CupBullet.h"


CupHeadScene::CupHeadScene()
{
	_player = make_shared<CupHead>();
	_bg = make_shared<CupBG>();
	_bg->SetPosition(Vector2(CENTER.x, 100.0f));
	_monster = make_shared<CupMonster>();
	_monster->SetPosition(Vector2(1100.0f, CENTER.y));
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	
	_player->GetCollider()->Block(_monster->GetCollider());

	if (_bg->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);
	

	if (_player->GetCollider()->Block(_monster->GetCollider()))


	for (auto bullet : _player->GetBullets())
	{
		bullet->Attack(_monster);
	}
	

	if (_monster->IsActive() == true)
	{
		for (auto bullet : _player->GetBullets())
		{
			//if (bullet->_isActive == false)
			//	continue;

			if (bullet->GetCollider()->IsCollision(_monster->GetCollider()))
			{
				_monster->TakeDamage(1);
				bullet->_isActive = false;
			}
		}
	}
	_player->Update();
	_monster->Update();
	_bg->Update();
}

void CupHeadScene::Render()
{
	_bg->Render();
	_monster->Render();
	_player->Render();

}

void CupHeadScene::PostRender()
{
	//ImGui::Text("Monster HP : %d ", _monster->GetHp());
	_player->PostRender();
	_monster->PostRender();
}

