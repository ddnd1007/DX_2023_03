#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 center, float height, float width)
	: _center(center), _height(height), _width(width)
{
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
	float left = _center.x - _width * 0.5f;
	float right = _center.x + _width * 0.5f;
	float bottom = _center.y + _height * 0.5f;
	float top = _center.y - _height * 0.5f;

	Rectangle(hdc, left, top, right, bottom);
}
