#include "framework.h"
#include "DunMonster.h"

DunMonster::DunMonster()
{
	_col = make_shared<RectCollider>(Vector2(40.0f, 40.0f));
	_quad = make_shared<Quad>(Vector2(80.0f, 80.0f), L"Resource/Texture/Winter.png");
	_quadTrans = make_shared<Transform>();
	_col->GetTransform()->SetPosition(CENTER);
	_quadTrans->SetParent(_col->GetTransform());
}

DunMonster::~DunMonster()
{
}

void DunMonster::Update()
{
	if (IsDead() == true)
		return;

	if (_isDamaged == true)
	{
		_curTime += DELTA_TIME;
	}

	if (_curTime > _damageTime)
	{
		_isDamaged = false;
		_curTime = 0.0f;
	}

	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	_col->Update();
	_quad->Update();
	_quadTrans->Update();
}

void DunMonster::Render()
{
	if (IsDead() == true)
		return;

	_col->Render();
	_quadTrans->SetWorldBuffer(0);
	_quad->Render();
}

void DunMonster::SetDir(Vector2 pos)
{
	Vector2 temp = pos - _col->GetWorldPos();
	temp.Normalize();
	_dir = temp;
}

void DunMonster::TakeDamage(int damage)
{
	if (_isDamaged == true)
		return;

	_hp -= damage;
	_isDamaged = true;
}