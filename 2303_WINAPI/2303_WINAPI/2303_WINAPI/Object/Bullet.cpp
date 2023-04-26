#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_circle = make_shared<CircleCollider>(10, Vector2(-100,-100));
	_pos = _circle->GetCenter();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_isActive == false) // 프레임 잡아먹지 않게 사용 안할때는 꺼지게 냅둠
		return;

	

	_pos += _direction * _speed;
	/*_direction.y += GRAVITY;*/

	_circle->SetCenter(_pos);
	_circle->Update();

	//if (_pos.x > WIN_WIDTH || _pos.x < 0) // 해상도를 넘어가면 bullet가 충전되게 만듦
	//	_isActive = false;
	//if (_pos.y > WIN_HEIGHT || _pos.y < 0)
	//	_isActive = false;
}

void Bullet::Render(HDC hdc)
{
	if (_isActive == false)
		return;

	_circle->Render(hdc);
}
