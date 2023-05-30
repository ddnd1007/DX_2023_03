#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Winter.png");

	_transform = make_shared
	

}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_transform->AddVector2(Vector2(0.01f, 0.01f));
	
	_transform->Update();
	_quad->Update();
}

void TutorialScene::Render()
{
	_transform->SetWorldBuffer(0);


	_quad->Render();
}