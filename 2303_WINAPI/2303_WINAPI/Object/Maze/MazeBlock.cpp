#include "framework.h"
#include "MazeBlock.h"

MazeBlock::MazeBlock()
{
	_rect =make_shared<RectCollider>(Vector2(), Vector2(14,14));

	_brushes.reserve(2);
	HBRUSH able = CreateSolidBrush(GREEN);
	HBRUSH disable = CreateSolidBrush(RED);
	HBRUSH player = CreateSolidBrush(GREY);
	HBRUSH end = CreateSolidBrush(BLUE);
	HBRUSH footprint = CreateSolidBrush(WHITE);

	_brushes.push_back(able);
	_brushes.push_back(disable);
	_brushes.push_back(player);
	_brushes.push_back(end);
	_brushes.push_back(footprint);
}

MazeBlock::~MazeBlock()
{
	for (auto brush : _brushes)
	{
		DeleteObject(brush);
	}
}

void MazeBlock::Update()
{
	_rect->Update();
}

void MazeBlock::Render(HDC hdc)
{
	if(_type == BlockType::NONE)
		return;

	SelectObject(hdc, _brushes[static_cast<unsigned int>(_type)]);
	_rect->Render(hdc);
}
