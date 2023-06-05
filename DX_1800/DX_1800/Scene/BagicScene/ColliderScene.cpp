#include "framework.h"
#include "ColliderScene.h"
#include "../../Types.h"

ColliderScene::ColliderScene()
{
	_mouseRect = make_shared<RectCollider>(Vector2(80.0f, 80.0f));
	_circleCollider = make_shared<CircleCollider>(100.0f);

	_colliders.push_back(_mouseRect);
	_colliders.push_back(_circleCollider);

	_mouseRect->GetTransform()->SetPosition(CENTER + Vector2(-100.0f, 0.0f));
	_circleCollider->GetTransform()->SetPosition(CENTER);
	
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_mouseRect->GetTransform()->SetPosition(MOUSE_POS);

	for (int i = 0; i < _colliders.size(); i++)
	{
		bool isCollision = false;
		for (int j = 0; j < _colliders.size(); j++)
		{
			if (i == j)
				continue;

			if (_colliders[i]->IsCollision(_colliders[j]))
				isCollision = true;
		}

		if (isCollision)
			_colliders[i]->SetColorRed();
		else
			_colliders[i]->SetColorGreen();
	}

	for (auto col : _colliders)
		col->Update();
}

void ColliderScene::Render()
{
	for (auto col : _colliders)
		col->Render();
}