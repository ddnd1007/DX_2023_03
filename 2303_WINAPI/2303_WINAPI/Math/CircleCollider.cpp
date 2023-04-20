#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(float radius, Vector2 center)
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	
}

void CircleCollider::Render(HDC)
{
	float left = _center.x = _radius;
	float right = _center.x + _radius;
}
