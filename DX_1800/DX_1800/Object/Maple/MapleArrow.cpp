#include "framework.h"
#include "MapleArrow.h"
#include "MapleMonster.h"

MapleArrow::MapleArrow()
{
	_quad = make_shared<Quad>(L"Resource/Maple/Character/arrrow.png", Vector2(200,200));
	_col = make_shared<CircleCollider>(5);
	_trans = make_shared<Transform>();

	_trans->SetParent(_col->GetTransform());
	_trans->SetPosition(Vector2(-80.0f, 0.0f));
	_trans->SetAngle(-PI * 0.5f);
	
	_col->GetTransform()->SetPosition(Vector2(-WIN_WIDTH * 5, -WIN_HEIGHT * 5));
	_isActive = false;

	_col->Update();
	_trans->Update();
}

MapleArrow::~MapleArrow()
{

}

void MapleArrow::Update()
{
	if (_isActive == false)
		return;

	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	_quad->Update();
	_col->Update();
	_trans->Update();

}

void MapleArrow::Render()
{
	if (_isActive == false)
		return;
	_trans->SetWorldBuffer(0);
	_quad->Render();
	_col->Render();
	
}

void MapleArrow::PostRender()
{

}

void MapleArrow::Attack(shared_ptr<class MapleMonster> victim)
{
	if (_isActive == false)
		return;
	if (_col->IsCollision(victim->GetCirCollider()) == false || victim->IsDead() == true)
		return;

	victim->TakeDamage(_damage);
	_isActive = false;
}



