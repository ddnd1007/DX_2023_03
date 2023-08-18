#include "framework.h"
#include "MapleBossScene.h"

#include "../../Object/Maple/MaplePlayer.h"
#include "../../Object/Maple/MapleMonster.h"
#include "../../Object/Maple/MapleArrow.h"
#include "../../Object/Maple/MapleBossMap.h"
#include "../../Object/Maple/MaplePortar.h"
#include "../../Object/Maple/Meso.h"

MapleBossScene::MapleBossScene()
{
	_player = make_shared<PlayerManager>();
	_bossMap = make_shared<MapleBossMap>();

	_bossMap->SetPosition(Vector2(0.0f, -350.0f));
	_portar = make_shared<MaplePortar>();
	_portar->SetPosition(Vector2(0.0f, -50.0f));
	
	CAMERA->SetTarget(_player->GetCollider()->GetTransform());
	CAMERA->SetLeftBottom(_bossMap->leftBottom());
	CAMERA->SetRightTop(_bossMap->rightTop());
	CAMERA->SetOffset(Vector2(0, -110));

}

MapleBossScene::~MapleBossScene()
{
}

void MapleBossScene::Update()
{
	_player->Update();
	_bossMap->Update();
	_portar->Update();

	if (_bossMap->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);

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
	
	_player->Render();
}

void MapleBossScene::PostRender()
{
}
