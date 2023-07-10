#include "framework.h"
#include "CupBG.h"

CupBG::CupBG()
{
	_quad = make_shared<Quad>(L"Resource/CupHead/track.png", Vector2(3000,300));
	_col = make_shared<RectCollider>(_quad->GetSize());
	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f,70.0f));
}

CupBG::~CupBG()
{
}

void CupBG::Update()
{
	_col->Update();
	_transform->Update();
	_quad->Update();
}

void CupBG::Render()
{
	_transform->SetWorldBuffer(0);
	_quad->Render();

	_col->Render();
}

Vector2 CupBG::leftBottom()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x - quadHalfSize.x;
	float y = -3000.0f;

	return Vector2(x,y);
}

Vector2 CupBG::rightTop()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _col->GetTransform()->GetWorldPos().x + quadHalfSize.x;
	float y = +3000.0f;

	return Vector2(x, y);
}
