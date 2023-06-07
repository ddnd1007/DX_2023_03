#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circleCollider = make_shared<CircleCollider>(50);
	_circleCollider->GetTransform()->SetPosition(CENTER);

	_rectCollider_Mouse = make_shared<RectCollider>(Vector2(90, 150));
	_rectCollider2 = make_shared<RectCollider>(Vector2(200,120));

	//_rectCollider2->GetTransform()->SetParent(_rectCollider_Mouse->GetTransform());

	_rectCollider2->GetTransform()->SetPosition(CENTER);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_circleCollider->Update();
	_rectCollider_Mouse->Update();
	_rectCollider2->Update();

	if (_rectCollider2->IsCollision(_rectCollider_Mouse))
	{
		_rectCollider2->SetColorRed();
		_rectCollider_Mouse->SetColorRed();
	}
	else
		_rectCollider2->SetColorGreen();
		_rectCollider_Mouse->SetColorGreen();

		_rectCollider_Mouse->GetTransform()->SetPosition(_pos);
		_rectCollider_Mouse->GetTransform()->SetScale(_scale);
		_rectCollider_Mouse->GetTransform()->SetAngle(_angle);
}

void ColliderScene::Render()
{
	_circleCollider->Render();
	_rectCollider_Mouse->Render();
	_rectCollider2->Render();
}

void ColliderScene::PostRender()
{
	ImGui::SliderFloat2("Pos", (float*)&_pos, 0, WIN_WIDTH, "%.0f");
	ImGui::SliderFloat2("Scale", (float*)&_scale, 0, 3, "%.1f");
	ImGui::SliderFloat("Angle", &_angle, 0, 2* PI, "%.1");
}
