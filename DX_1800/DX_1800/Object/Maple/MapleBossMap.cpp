#include "framework.h"
#include "MapleBossMap.h"

MapleBossMap::MapleBossMap()
{
	_quad = make_shared<Quad>(L"Resource/Maple/map/bossMap.png");
	_col = make_shared<RectCollider>(Vector2(2000, 500));
	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f, 440.0f));
}

MapleBossMap::~MapleBossMap()
{
}

void MapleBossMap::Update()
{
	_col->Update();
	_transform->Update();

	_quad->Update();
}

void MapleBossMap::Render()
{
	_transform->SetWorldBuffer(0);
	_quad->Render();

	_col->Render();
}

Vector2 MapleBossMap::leftBottom()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x - quadHalfSize.x;
	float y = -3000.0f;

	return Vector2(x, y);
}

Vector2 MapleBossMap::rightTop()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x + quadHalfSize.x;
	float y = +3000.0f;

	return Vector2(x, y);
}
