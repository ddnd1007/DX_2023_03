#include "framework.h"
#include "LineCollisionScene.h"

LineCollisionScene::LineCollisionScene()
{
	_line1 = make_shared<Line>(Vector2(100,120), Vector2(500,500));
	_line2 = make_shared<Line>(Vector2(100,600), Vector2(500,500));

	
}

LineCollisionScene::~LineCollisionScene()
{
}

void LineCollisionScene::Update()
{
	_line2->_endPos = mousePos;

	if (_line2->IsCollision(_line1))
	{
		_line1->SetRed();
		_line2->SetRed();

	}
	else
	{
		_line1->SetGreen();
		_line2->SetGreen();
	}
	
}

void LineCollisionScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
}
