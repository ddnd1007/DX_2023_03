#include "framework.h"
#include "ArkanoidBrick.h"

ArkanoidBrick::ArkanoidBrick()
{
	_rect = make_shared<RectCollider>(CENTER, Vector2(50, 20));

	HBRUSH brick = CreateSolidBrush(GRAY);
	HBRUSH none = CreateSolidBrush(WHITE);

	_brushes.reserve(2);
	_brushes.push_back(brick);
	_brushes.push_back(none);

}

ArkanoidBrick::~ArkanoidBrick()
{
	for (auto& brush : _brushes)
		DeleteObject(brush);
}

void ArkanoidBrick::Update()
{
	if (_isDead == true)
		return;
	_rect->Update();
}

void ArkanoidBrick::Render(HDC hdc)
{
	if (_isDead == true)
		return;
	SelectObject(hdc, _brushes[static_cast<UINT>(_type)]);
	_rect->Render(hdc);
}
