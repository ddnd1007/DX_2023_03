#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/Obj/CupHead/CupHead.h"
#include "../../Object/Obj/CupHead/CupBG.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<CupHead>();
	_bg = make_shared<CupBG>();
	_bg->SetPosition(Vector2(0.0f, -300.0f));

	CAMERA->SetTarget(_player->GetCollider()->GetTransform());
	CAMERA->SetLeftBottom(_bg->leftBottom());
	CAMERA->SetRightTop(_bg->rightTop());
	//CAMERA->SetOffset(Vector2(100,0));
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
	_bg->Update();

	if(_bg->GetCollider()->Block(_player->GetCollider()))
		_player->Grounded();
	else
		_player->SetIsFalling(true);

}

void CupHeadScene::Render()
{
	_bg->Render();
	_player->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
}
