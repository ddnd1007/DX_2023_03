#include "framework.h"
#include "Vector2.h"

bool Vector2::IsBetween(Vector2 v1, Vector2 v2)
{
	float cross1 = v1.Cross(*this);
	float cross2 = v2.Cross(*this);

	if ((cross1 * cross2) < 0.0f)
		return true;

	return false;
}

Vector2 Vector2::Normallize()
{
	float legnth = this->Length();
	return Vector2(x / legnth, y / legnth);
}