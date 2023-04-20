#include "framework.h"
#include "Line.h"

Line::~Line()
{
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, _startPos.x, _startPos.y, nullptr);
	LineTo(hdc, _endPos.x, _endPos.y);
}

Line::Result Line::IsCollision(shared_ptr<Line> other)
{
    Result myresult;

    Vector2 floorLineVec = _endPos - _startPos;
    Vector2 floorLineToEnd = other->_endPos - _startPos;
    Vector2 floorLineToStart = other->_startPos - _startPos;

    bool between1 = floorLineVec.IsBetween(floorLineToEnd, floorLineToStart);

    Vector2 mouseLineVec = other->_endPos - other->_startPos;
    Vector2 mouseLineToEnd = _endPos - other->_startPos;
    Vector2 mouseLineToStart = _startPos - other->_startPos;

    bool between2 = mouseLineVec.IsBetween(mouseLineToEnd, mouseLineToStart);

    if (between1 == true && between2 == true)
    {
        myresult.collision = true;

         
        float leftTriangle = abs(mouseLineVec.Cross(floorLineToStart));
        float rightTriangle = abs(mouseLineVec.Cross(mouseLineToEnd));

        float t = (leftTriangle) / (rightTriangle + leftTriangle);
        Vector2 conflict = LERP(_startPos, _endPos, t);
        myresult.conflict = conflict;
    }
    else
    {
        myresult.collision = false;
    }

    return myresult;
}





