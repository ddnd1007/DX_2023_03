#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	//_circleCollider = make_shared<CircleCollider>(50);
	//_circleColliderMouse = make_shared<CircleCollider>(100);
	//_rectColliderKeyBoard = make_shared<RectCollider>(Vector2(90,150));
	//_rectCollider2  = make_shared<RectCollider>(Vector2(200,120));

	_circleColliderMouse = make_shared<CircleCollider>(100);
	_rectCollider2 = make_shared<RectCollider>(Vector2(100, 50));
	_rectColliderKeyBoard = make_shared<RectCollider>(Vector2(100, 200));
	_circleCollider = make_shared<CircleCollider>(80);
	_rectCollider2->GetTransform()->SetPosition(CENTER);
	_circleCollider->GetTransform()->SetPosition(CENTER);

}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_circleColliderMouse->GetTransform()->SetPosition(MOUSE_POS);

	if (KEY_PRESS('W'))
	{
		_rectColliderKeyBoard->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * DELTA_TIME * 500.0f);
	}
	if (KEY_PRESS('S'))
	{
		_rectColliderKeyBoard->GetTransform()->AddVector2(Vector2(0.0f, -1.0f) * DELTA_TIME * 500.0f);
	}
	if (KEY_PRESS('D'))
	{
		_rectColliderKeyBoard->GetTransform()->AddVector2(Vector2(1.0f, 0.0f) * DELTA_TIME * 500.0f);
	}
	if (KEY_PRESS('A'))
	{
		_rectColliderKeyBoard->GetTransform()->AddVector2(Vector2(-1.0f, 0.0f) * DELTA_TIME * 500.0f);
	}

	_circleColliderMouse->Update();
	_circleCollider->Update();
	_rectCollider2->Update();
	_rectColliderKeyBoard->Update();

	_circleColliderMouse->Block(_circleCollider);
	_rectColliderKeyBoard->Block(_rectCollider2);
	_rectColliderKeyBoard->Block(_circleCollider);

	if (_rectColliderKeyBoard->IsOBB(_circleCollider))
	{
		_rectColliderKeyBoard->SetColorRed();
		_circleCollider->SetColorRed();
	}
	else
	{
		_rectColliderKeyBoard->SetColorGreen();
		_circleCollider->SetColorGreen();
	}
	//_rectColliderMouse->GetTransform()->SetPosition(_pos);
	_rectColliderKeyBoard->GetTransform()->SetScale(_scale);
	_rectColliderKeyBoard->GetTransform()->SetAngle(_angle);
}

void ColliderScene::Render()
{
	//_circleCollider->Render();
	//if (_isActive)
		//_circleColliderMouse->Render();
	//_circleColliderMouse->Render();
	_circleCollider->Render();
	//_rectCollider2->Render();
	_rectColliderKeyBoard->Render();
}

void ColliderScene::PostRender()
{
	ImGui::SliderFloat2("Pos", (float*)&_pos, 0, WIN_WIDTH, "%.0f");
	ImGui::SliderFloat2("Scale", (float*)&_scale, 0, 3, "%.1f");
	ImGui::SliderFloat("Angle", &_angle, 0, 2 * PI, "%.1f");
}
