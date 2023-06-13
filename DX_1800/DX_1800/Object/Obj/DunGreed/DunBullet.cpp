#include "framework.h"
#include "DunBullet.h"
#include "DunMonster.h"

DunBullet::DunBullet()
{
	_quad = make_shared<Quad>(Vector2(30, 30), L"Resource/Texture/Bullet.png");
	_quadTrans = make_shared<Transform>();
	_col = make_shared<CircleCollider>(15.0f);

	_quadTrans->SetParent(_col->GetTransform());
}

DunBullet::~DunBullet()
{
}

void DunBullet::Update()
{
	if (_isActive == false)
		return;

	if (_pos.x > WIN_WIDTH || _pos.x < 0.0f)
		_isActive = false;
	if (_pos.y > WIN_HEIGHT || _pos.y < 0.0f)
		_isActive = false;

	_pos += _dir * _speed * DELTA_TIME;
	_col->GetTransform()->SetPosition(_pos);
	_col->GetTransform()->SetAngle(_dir.Angle());
	_quadTrans->Update();
	_quad->Update();
	_col->Update();
}

void DunBullet::Render()
{
	if (_isActive == false)
		return;

	_quadTrans->SetWorldBuffer(0);
	_quad->Render();
	_col->Render();
}

void DunBullet::Attack(shared_ptr<DunMonster> victim)
{
	if (_isActive == false)
		return;
	if (_col->IsCollision(victim->GetCollider()) == false || victim->IsDead() == true)
		return;

	victim->TakeDamage(_damage);
	_isActive = false;
}
