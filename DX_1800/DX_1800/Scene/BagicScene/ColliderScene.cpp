#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(100.0f, 80.0f));
	_rectCollider->GetTransform()->SetPosition(CENTER);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->Update();
}

void ColliderScene::Render()
{
	_rectCollider->Render();
}
