#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
	_circle = make_shared<CircleCollider>(50, Vector2(400,400))
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
	// circle콜라이더의 중심이 마우스를 따라 움직여라
}

void PaintScene::Render(HDC hdc)
{
	
	_circle->Render(hdc);
}
