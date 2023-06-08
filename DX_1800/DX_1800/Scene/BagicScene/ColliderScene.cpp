#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circleCollider = make_shared<CircleCollider>(50);
	_circleCollider->GetTransform()->SetPosition(CENTER);

	_rectColliderMouse = make_shared<RectCollider>(Vector2(90, 150));
	_rectCollider2 = make_shared<RectCollider>(Vector2(200, 120));

	_rectCollider2->GetTransform()->SetPosition(CENTER);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	if (KEY_PRESS('W'))
		_rectColliderMouse->GetTransform()->AddVector2({ 0.0f,1.0f } * DELTA_TIME);
	if (KEY_PRESS('S'))
		_rectColliderMouse->GetTransform()->AddVector2({ 0.0f,-1.0f } * DELTA_TIME);
	if (KEY_PRESS('A'))
		_rectColliderMouse->GetTransform()->AddVector2({ 1.0f,1.0f } * DELTA_TIME);
	if (KEY_PRESS('D'))
		_rectColliderMouse->GetTransform()->AddVector2({ -1.0f,1.0f } * DELTA_TIME);


	_circleCollider->Update();
	_rectColliderMouse->Update();
	_rectCollider2->Update();

	if (_rectColliderMouse->IsOBB(_circleCollider))
	{
		_circleCollider->SetColorRed();
		_rectColliderMouse->SetColorRed();
	}
	else
	{
		_circleCollider->SetColorGreen();
		_rectColliderMouse->SetColorGreen();
	}

	//_rectColliderMouse->GetTransform()->SetPosition(_pos);
	_rectColliderMouse->GetTransform()->SetScale(_scale);
	_rectColliderMouse->GetTransform()->SetAngle(_angle);
}

void ColliderScene::Render()
{
	_circleCollider->Render();
	_rectColliderMouse->Render();
	_rectCollider2->Render();
}

void ColliderScene::PostRender()
{
	//ImGui::SliderFloat2("Pos", (float*)&_pos, 0, WIN_WIDTH, "%.0f");
	ImGui::SliderFloat2("Scale", (float*)&_scale, 0, 3, "%.1f");
	ImGui::SliderFloat("Angle", &_angle, 0, 2 * PI, "%.1f");
}