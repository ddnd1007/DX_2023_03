#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circleCollider = make_shared<CircleCollider>(50);
	_circleCollider->GetTransform()->SetPosition(CENTER);

	_rectColliderMouse = make_shared<RectCollider>(Vector2(90, 150));
<<<<<<< HEAD
	_circleColliderMouse = make_shared<CircleCollider>(100);
=======
>>>>>>> a27384b77adc5a66fba97ad6d8794dd805460d14
	_rectCollider2 = make_shared<RectCollider>(Vector2(200, 120));

	_rectCollider2->GetTransform()->SetPosition(CENTER);
}

// 오류 발생할 시 setposition에 updatesrt 추가

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
<<<<<<< HEAD
	_circleColliderMouse->GetTransform()->SetPosition(MOUSE_POS);
=======
>>>>>>> a27384b77adc5a66fba97ad6d8794dd805460d14
	if (KEY_PRESS('W'))
		_rectColliderMouse->GetTransform()->AddVector2({ 0.0f,1.0f } * DELTA_TIME);
	if (KEY_PRESS('S'))
		_rectColliderMouse->GetTransform()->AddVector2({ 0.0f,-1.0f } * DELTA_TIME);
	if (KEY_PRESS('A'))
		_rectColliderMouse->GetTransform()->AddVector2({ 1.0f,1.0f } * DELTA_TIME);
	if (KEY_PRESS('D'))
		_rectColliderMouse->GetTransform()->AddVector2({ -1.0f,1.0f } * DELTA_TIME);

<<<<<<< HEAD
	_circleColliderMouse->Update();
=======

>>>>>>> a27384b77adc5a66fba97ad6d8794dd805460d14
	_circleCollider->Update();
	_rectColliderMouse->Update();
	_rectCollider2->Update();

<<<<<<< HEAD
	_circleColliderMouse->Block(_circleCollider);
	_rectColliderMouse->Block(_rectCollider2);

=======
>>>>>>> a27384b77adc5a66fba97ad6d8794dd805460d14
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
	_circleColliderMouse->Render();
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