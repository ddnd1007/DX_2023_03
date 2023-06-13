#include "framework.h"
#include "SpriteScene.h"

SpriteScene::SpriteScene()
{
	_zelda = make_shared<Zelda>(L"Resource/Texture/zelda.png", Vector2(10, 8), Vector2(200, 200));
}

SpriteScene::~SpriteScene()
{
}

void SpriteScene::Update()
{
	_zelda->Update();
}

void SpriteScene::Render()
{
	_zelda->Render();
}

//void SpriteScene::PostRender()
//{
//	ImGui::SliderFloat2("CurFrame", (float*)&_curFrame.x, 0, 10, "%.0f");
//
//	_sprite->SetCurFrame(_curFrame);
//}
