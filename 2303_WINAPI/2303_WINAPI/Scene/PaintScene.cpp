#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
	_circle = make_shared<CircleCollider>(50, Vector2(400, 400));
	_rect = make_shared<RectCollider>(Vector2(300, 300), 150, 200);
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
	// circle콜라이더의 중심이 마우스를 따라 움직여라
	// 선형보간
	Vector2 rectlerpPos = LERP(_rect->GetCenter(), mousePos, 0.4f);
	Vector2 lerpPos = LERP(_circle->GetCenter(), mousePos, 0.1f);

	_rect->SetCenter(rectlerpPos);
	_circle->SetCenter(lerpPos);
	
}

void PaintScene::Render(HDC hdc)
{
	_rect->Render(hdc);
	_circle->Render(hdc);
	
}
