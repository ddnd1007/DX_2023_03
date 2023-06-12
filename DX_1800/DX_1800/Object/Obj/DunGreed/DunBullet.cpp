#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png");
	_collider = make_shared<CircleCollider>(0.1f);

	_quad->GetTransform()->SetParent(_collider->GetTransform());
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

	if (_pos.x > WIN_WIDTH || _pos.x < 0.0f)
		_isActive = false;
	if (_pos.y > WIN_HEIGHT || _pos.y < 0.0f)
		_isActive = false;

	_pos += _dir * _speed * DELTA_TIME;
	_collider->GetTransform()->SetPosition(_pos);
	_quad->GetTransform()->SetAngle(_dir.Angle());
	_collider->Update();

}

void DunBullet::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_collider->Render();
}

void DunBullet::Attack(shared_ptr<DunBoss> victim)
{
	if (_isActive == false)
		return;
	if (_collider->Block(victim->GetCollider()) == false || victim->_isActive == false)
		return;

	victim->TakeDamage(_damage);
	_isActive = false;
}

