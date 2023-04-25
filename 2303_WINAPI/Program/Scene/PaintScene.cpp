#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
}

PaintScene::~PaintScene()
{

}

void PaintScene::Update()
{
	
}

void PaintScene::Render(HDC hdc)
{
	Ellipse(hdc, mousePos.x, mousePos.y, 700,700);
}
