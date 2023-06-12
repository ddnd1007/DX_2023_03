#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet()
{
	_col = make_shared<CircleCollider>(15.0f); // 루트 컴포넌트로 통일
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png", Vector2(30,30));

	_quad->GetTransform()->SetParent(_col->GetTransform());
	_quad->GetTransform()->SetScale(Vector2(0.1f, 0.1f));
	_quad->GetTransform()->SetPosition(Vector2(-100.0f, -100.0f));
}

DunBullet::~DunBullet()
{

}

void DunBullet::Update()
{
	if (_isActive == false)
		return;

	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	_col->Update();
	_quad->Update();

}

void DunBullet::Render()
{
	if (_isActive == false)
		return;

	_col->Render();
	_quad->Render();
}

void DunBullet::Fire(Vector2 stratPos, Vector2 dir)
{
	_isActive = true;
	_dir = dir;

	_col->GetTransform()->SetAngle(dir.Angle());
	_col->GetTransform()->SetPosition(stratPos);
}

void DunBullet::InPut()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 start = bowQuad->GetTransform()->GetWorldPos();

		Vector2 direction
	}
}


