#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider()
{
	CreatePens();
}

RectCollider::RectCollider(Vector2 center, Vector2 size)
	: _center(center)
	, _size(size)
{
	CreatePens();
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPenIdex]);

	float left = _center.x - _size.x * 0.5f;
	float right = _center.x + _size.x * 0.5f;
	float top = _center.y - _size.y * 0.5f;
	float bottom = _center.y + _size.y * 0.5f;

	Rectangle(hdc, left, top, right, bottom);
}

bool RectCollider::IsCollision(const Vector2& pos)
{
	if (pos.x < Right() && pos.x > Left())
	{
		if (pos.y < Bottom() && pos.y > Top())
			return true;
	}

	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	if (Left() > other->Right() || Right() < other->Left())
		return false;

	if (Top() > other->Bottom() || Bottom() < other->Top())
		return false;

	return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector2 leftTop = Vector2(Left(), Top());
	Vector2 leftBottom = Vector2(Left(), Bottom());
	Vector2 rightTop = Vector2(Right(), Top());
	Vector2 rightBottom = Vector2(Right(), Bottom());

	if (other->IsCollision(leftTop) || other->IsCollision(leftBottom)
		|| other->IsCollision(rightTop) || other->IsCollision(rightBottom))
		return true;

	if (Right() > other->GetCenter().x && Left() < other->GetCenter().x)
	{
		if (Top() - other->GetRadius() < other->GetCenter().y
			&& Bottom() + other->GetRadius() > other->GetCenter().y)
			return true;
	}

	if (Bottom() > other->GetCenter().y && Top() < other->GetCenter().y)
	{
		if (Left() - other->GetRadius() < other->GetCenter().x
			&& Right() + other->GetRadius() > other->GetCenter().x)
			return true;
	}

	return false;
}

void RectCollider::SetCenter(const Vector2& center)
{
	_center = center;
}

void RectCollider::CreatePens()
{
	_curPenIdex = 0;
	_pens.emplace_back(CreatePen(PS_SOLID, 3, GREEN)); // 0
	_pens.emplace_back(CreatePen(PS_SOLID, 3, RED));   // 1
}
