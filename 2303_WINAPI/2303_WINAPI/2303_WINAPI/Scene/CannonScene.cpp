#include "framework.h"
#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>();
	_cannon2 = make_shared<Cannon>();
	_cannon2 = isControll = false
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{

	_cannon->Update();
	_cannon2->Update();
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_cannon2->Render(hdc);
}
