#include "framework.h"
#include "Vector2.h"

bool Vector2::operator==(const Vector2& other) const
{
    return (x == other.x) && (y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !this->operator==(other);
}

bool Vector2::IsBetween(Vector2 a, Vector2 b)
{
    float crossA = this->Cross(a);
    float crossB = this->Cross(b);

    return crossA * crossB < 0;
}
