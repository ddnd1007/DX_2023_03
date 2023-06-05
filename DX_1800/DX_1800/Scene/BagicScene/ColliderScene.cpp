#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circleCollider = make_shared<CircleCollider>(50);
	_circleCollider->GetTransform()->SetPosition(CENTER);

	_rectCollider = make_shared<RectCollider>(Vector2(90, 150));
	_rectCollider2 = make_shared<RectCollider>(Vector2(40, 70));

	_rectCollider2->GetTransform()->SetParent(_rectCollider->GetTransform());
	_rectCollider2->GetTransform()->SetPosition({ 100.0f,0.0f });
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->GetTransform()->SetPosition(MOUSE_POS);

	_circleCollider->Update();
	_rectCollider->Update();
	_rectCollider2->Update();

	if (_rectCollider2->IsCollision(_circleCollider))
	{
		_rectCollider2->SetColorRed();
	}
	else
		_rectCollider2->SetColorGreen();
}

void ColliderScene::Render()
{
	_circleCollider->Render();
	_rectCollider->Render();
	_rectCollider2->Render();
}
