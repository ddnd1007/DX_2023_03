#include "framework.h"
#include "ZeldaScene.h"

#include "Object/Obj/Zelda/Zelda.h"

ZeldaScene::ZeldaScene()
{
	_zelda = make_shared<Zelda>();

	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(100,30));
	_button->SetEvent(std::bind(&ZeldaScene::CameraShake, this));
}

ZeldaScene::~ZeldaScene()
{
}

void ZeldaScene::Update()
{
	_zelda->Update();
	_button->Update();
}

void ZeldaScene::Render()
{
	_zelda->Render();
}

void ZeldaScene::PostRender()
{
	_button->PostRender();
}

void ZeldaScene::CameraShake()
{
	CAMERA->ShakeStart(5.0f,1.0f);
}
