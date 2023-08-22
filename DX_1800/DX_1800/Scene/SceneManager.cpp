#include "framework.h"
#include "SceneManager.h"

#include "../Object/Maple/PlayerManager.h"
#include "../Object/Maple/MapleMap.h"
#include "../Object/Maple/MapleBossMap.h"
#include "BagicScene/MapleBossScene.h"
#include "BagicScene/MapleScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	_player = make_shared<PlayerManager>();
	_map = make_shared<MapleMap>();
	_bossMap = make_shared<MapleBossMap>();

	_scenes.push_back(make_shared<MapleScene>());
	_scenes.push_back(make_shared<MapleBossScene>());

	CAMERA->SetTarget(_player->GetCollider()->GetTransform());
	CAMERA->SetLeftBottom(_map->leftBottom());
	CAMERA->SetRightTop(_map->rightTop());
	CAMERA->SetOffset(Vector2(0, -110));
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	_scenes[_curScene]->Update();
}

void SceneManager::Render()
{
	_scenes[_curScene]->Render();
}

void SceneManager::PreRender()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();

	_scenes[_curScene]->preRender();

}

void SceneManager::PostRender()
{
	_scenes[_curScene]->PostRender();

	if (ImGui::Button("NextScene", { 130,30 }))
		NextScene();

	if (ImGui::Button("PrevScene", { 130,30 }))
		PrevScene();

	if (ImGui::Button("SetScene", { 130,30 }))
		SetScene(_test);

	ImGui::SliderInt("SetSceneNumber", (int*)&_test, 0, 1);
}

void SceneManager::NextScene()
{
	if (_curScene >= _scenes.size() - 1)
		return;

	CAMERA->SetLeftBottom(_bossMap->leftBottom());
	CAMERA->SetRightTop(_bossMap->rightTop());

	_scenes[_curScene]->End();
	++_curScene;
	_scenes[_curScene]->Init();
}

void SceneManager::PrevScene()
{
	if (_curScene <= 0)
		return;

	CAMERA->SetLeftBottom(_map->leftBottom());
	CAMERA->SetRightTop(_map->rightTop());

	_scenes[_curScene]->End();
	--_curScene;
	_scenes[_curScene]->Init();
}

void SceneManager::SetScene(int number)
{
	if (number >= _scenes.size() - 1 || number < 0)
		return;

	_scenes[_curScene]->End();
	_curScene = number;
	_scenes[_curScene]->Init();
}
