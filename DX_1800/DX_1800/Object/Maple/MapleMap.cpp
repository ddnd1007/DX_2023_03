#include "framework.h"
#include "MapleMap.h"

MapleMap::MapleMap()
{
	_quad = make_shared<Quad>(L"Resource/Maple/map/chobomap.png");
	_col = make_shared<RectCollider>(Vector2(2000,30));
	_col2 = make_shared<RectCollider>(Vector2(1000,700));
	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetParent(_col2->GetTransform());
	_transform->SetPosition(Vector2(0.0f, -70.0f));
}

MapleMap::~MapleMap()
{
}

void MapleMap::Update()
{
	_col->Update();
	_col2->Update();
	_transform->Update();
	
	_quad->Update();
}

void MapleMap::Render()
{
	_transform->SetWorldBuffer(0);
	_quad->Render();
	
	_col->Render();
	_col2->Render();
}

Vector2 MapleMap::leftBottom()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x - quadHalfSize.x;
	float y = -3000.0f;

	return Vector2(x, y);
}

Vector2 MapleMap::rightTop()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x + quadHalfSize.x;
	float y = +3000.0f;

	return Vector2(x, y);
}
