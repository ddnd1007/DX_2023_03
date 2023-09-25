#include "framework.h"
#include "MapleMap.h"
#include "MaplePortar.h"

MapleMap::MapleMap()
{
	_quad = make_shared<Quad>(L"Resource/Maple/map/chobomap.png");
	_col = make_shared<RectCollider>(Vector2(2000,500));
	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f,440.0f));
}

MapleMap::~MapleMap()
{
}

void MapleMap::Update()
{
	
	_col->Update();
	_transform->Update();
	
	_quad->Update();
}

void MapleMap::Render()
{
	_transform->SetWorldBuffer(0);
	_quad->Render();
	
	//_col->Render();
}

Vector2 MapleMap::leftBottom()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x - quadHalfSize.x;
	float y = -2000.0f;

	return Vector2(x, y);
}

Vector2 MapleMap::rightTop()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x + quadHalfSize.x;
	float y = +2000.0f;

	return Vector2(x, y);
}
