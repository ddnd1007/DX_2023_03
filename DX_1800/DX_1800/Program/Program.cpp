#include "framework.h"
#include "Program.h"

#include "../Scene/BagicScene/MapleScene.h"
#include "../Scene/BagicScene/MapleBossScene.h"

Program::Program()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Timer::GetInstance()->LockFPS(60);
}

Program::~Program()
{
}

void Program::Update()
{
	Timer::GetInstance()->Update();
	InputManager::GetInstance()->Update();

	//CAMERA->Update();
	SCENE->Update();

	EFFECT->Update();
	SOUND->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	SCENE->Render();
	//CAMERA->SetViewBuffer();
	//CAMERA->SetProjectionBuffer();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();
	//CAMERA->SetUIViewBuffer();
	//CAMERA->PostRender();
	EFFECT->Render();

	SCENE->PostRender();

	ImGui::Text("FPS : %d", FPS);
	ImGui::Text("DeltaTime : %1f", DELTA_TIME);
	ImGui::Text("RunTime : %1f", RUN_TIME);
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
