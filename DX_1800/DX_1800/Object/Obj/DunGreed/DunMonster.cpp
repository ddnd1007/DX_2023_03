#include "framework.h"
#include "DunMonster.h"

DunMonster::DunMonster()
{
	_col = make_shared<RectCollider>(Vector2(250,150));
	_quad = make_shared<Quad>(L"Resource/Texture/Winter.png", Vector2(245,145));
	_trans = make_shared<Transform>();
	_trans->SetParent(_col->GetTransform());

	_hpBar = make_shared<HpBar>();

	_hpBar->SetPosition(Vector2(0,250));
}

DunMonster::~DunMonster()
{
}

void DunMonster::Update()
{
	if(IsActive() == false)
		return;

	_col->Update();
	_trans->Update();
	_quad->Update();
	_hpBar->Update();
}

void DunMonster::Render()
{
	if (IsActive() == false)
		return;

	_col->Render();

	_trans->SetWorldBuffer(0);
	_quad->Render();
}

void DunMonster::PostRender()
{
	_hpBar->PostRender();
}

void DunMonster::TakeDamage(int amount)
{
	_hp -= amount;

	_hpBar->SetRatio(_hp / (float)_maxHp);
}
