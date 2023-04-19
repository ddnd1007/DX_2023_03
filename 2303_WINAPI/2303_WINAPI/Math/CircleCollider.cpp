#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius, Vector2 center)
	: _radius(radius)
	, _center(center)
{
}


void CircleCollider::Update()
{
}

void CircleCollider::Render(HDC hdc)
{
	float left = _center.x - _radius;
	float right = _center.x + _radius;
	float top = _center.y - _radius;
	float bottom = _center.y + _radius;

	Ellipse(hdc, left, top, right, bottom);
}
