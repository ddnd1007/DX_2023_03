#pragma once
#include "framework.h"

class Zelda
{
public:
	Zelda(wstring path, Vector2 maxFrame, Vector2 size);
	~Zelda();

	void Update();
	void Render();

	void CreateVertices();
	void CreateData(wstring path);

//adfsadf

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _spriteTrans;
	shared_ptr<ActionBuffer> _actionBuffer;
};