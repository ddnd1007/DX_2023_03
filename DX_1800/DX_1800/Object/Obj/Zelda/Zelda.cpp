#include "framework.h"
#include "Zelda.h"

Zelda::Zelda(wstring path, Vector2 maxFrame, Vector2 size)
{
	_sprite = make_shared<Sprite>(path, maxFrame, size);
	_spriteTrans = make_shared<Transform>();
	_spriteTrans->SetPosition(CENTER);

	_sprite->CreateVertices();
	_sprite->CreateData(path);
	//asdfasdfasdf
}

Zelda::~Zelda()
{
}

void Zelda::Update()
{
	if (KEY_PRESS('A'))
	{
		_sprite->SetCurClip(Vector2(0, 1));
	}
	if (KEY_PRESS('D'))
	{
		_sprite->SetCurClip(Vector2(0, 3));
	}
	if (KEY_PRESS('W'))
	{
		_sprite->SetCurClip(Vector2(0, 2));
	}
	if (KEY_PRESS('S'))
	{
		_sprite->SetCurClip(Vector2(0, 0));
	}

	_actionBuffer->Update_Resource();
	_spriteTrans->Update();
	_sprite->Update();
}

void Zelda::Render()
{
	_actionBuffer->SetPS_Buffer(0);
	_spriteTrans->SetWorldBuffer(0);
	_sprite->Render();
}

void Zelda::CreateVertices()
{
	_sprite->CreateVertices();
}

void Zelda::CreateData(wstring path)
{
	_sprite->CreateData(path);
}






