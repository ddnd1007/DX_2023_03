#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png");
	_quad->GetTransform()->SetScale(Vector2{ 0.1f, 0.1f });
	_quad->GetTransform()->SetPosition(Vector2{ -100.0f, 0.0f });
}

DunBullet::~DunBullet()
{
}

void DunBullet::Update()
{
	if (_isActive == false)
		return;

	if (_pos.x > WIN_WIDTH || _pos.x < 0)
		_isActive = false;
	if (_pos.y > WIN_HEIGHT || _pos.y < 0)
		_isActive == false;

	_pos += _dir * _speed;
	_quad->GetTransform()->SetPosition(_pos);
	_quad->GetTransform()->SetAngle(_dir.Angle());
	_quad->Update();

}

void DunBullet::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
}


