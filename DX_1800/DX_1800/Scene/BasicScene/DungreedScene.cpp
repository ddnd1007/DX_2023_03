#include "framework.h"
#include "DungreedScene.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<DunPlayer>(L"Player.png");
	_arrow = make_shared<DunPlayer>(L"item11x5.jpg");
	_bullet = make_shared<DunBullet>(L"Bullet.png");

}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
}

void DungreedScene::Render()
{
}
