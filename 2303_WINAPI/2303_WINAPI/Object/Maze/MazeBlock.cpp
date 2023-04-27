#include "framework.h"
#include "MazeBlock.h"

MazeBlock::MazeBlock()
{
<<<<<<< HEAD
	_rect =make_shared<RectCollider>(Vector2(), Vector2(14,14));
=======
	_rect = make_shared<RectCollider>(Vector2(), Vector2(14, 14));
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1

	_brushes.reserve(2);
	HBRUSH able = CreateSolidBrush(GREEN);
	HBRUSH disable = CreateSolidBrush(RED);
<<<<<<< HEAD
	HBRUSH player = CreateSolidBrush(GREY);
	HBRUSH end = CreateSolidBrush(BLUE);
	HBRUSH footprint = CreateSolidBrush(WHITE);
=======
	HBRUSH player = CreateSolidBrush(GRAY);
	HBRUSH end = CreateSolidBrush(BLUE);
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1

	_brushes.push_back(able);
	_brushes.push_back(disable);
	_brushes.push_back(player);
	_brushes.push_back(end);
<<<<<<< HEAD
	_brushes.push_back(footprint);
=======
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
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
<<<<<<< HEAD
	if(_type == BlockType::NONE)
=======
	if (_type == BlockType::NONE)
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
		return;

	SelectObject(hdc, _brushes[static_cast<unsigned int>(_type)]);
	_rect->Render(hdc);
}
