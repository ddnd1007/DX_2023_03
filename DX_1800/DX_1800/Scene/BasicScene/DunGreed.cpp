#include "framework.h"
#include "DunGreed.h"

DunGreed::DunGreed()
{
	_player = make_shared<DunPlayer>();
}

DunGreed::~DunGreed()
{
}

void DunGreed::Update()
{
	_player->Update();
}

void DunGreed::Render()
{
	_player->Render();
}
