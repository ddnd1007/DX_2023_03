#include "framework.h"
#include "Program.h"

Program::Program()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	FONT->GetInstance();

	FONT->Add("D2Coding", L"D2Coding");

	Timer::GetInstance()->LockFPS(60);
}

Program::~Program()
{
	FONT->Delete();
}

void Program::Update()
{
	Timer::GetInstance()->Update();
	InputManager::GetInstance()->Update();

	SCENE->Update();
	CAMERA->Update();

	EFFECT->Update();
	SOUND->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	CAMERA->SetViewBuffer();
	CAMERA->SetProjectionBuffer();

	FONT->GetInstance()->GetDC()->BeginDraw();

	SCENE->Render();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();


	CAMERA->SetUIViewBuffer();
	CAMERA->PostRender();
	EFFECT->Render();

	SCENE->PostRender();
	FONT->GetInstance()->GetDC()->EndDraw();

	ImGui::Text("FPS : %d", FPS);
	ImGui::Text("DeltaTime : %1f", DELTA_TIME);
	ImGui::Text("RunTime : %1f", RUN_TIME);


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
