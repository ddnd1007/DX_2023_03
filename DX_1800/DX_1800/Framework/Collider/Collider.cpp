#include "framework.h"
#include "Collider.h"

Collider::Collider()
{
	_transform = make_shared<Transform>();
}

Collider::~Collider()
{

}

void Collider::Update()
{

}

void Collider::Render()
{

}


bool Collider::IsCollision(shared_ptr<Collider> other)
{
	switch (other->_type)
	{
	case Collider::Type::NONE:
		return false;
	case Collider::Type::CIRCLE:
		return IsCollision(dynamic_pointer_cast<CircleCollider>(other));
	case Collider::Type::RECT:
		return IsCollision(dynamic_pointer_cast<RectCollider>(other));
	default:
		return false;
	}
}
