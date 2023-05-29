#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Winter.png");

	_world = make_shared<MatrixBuffer>();
	_view = make_shared<MatrixBuffer>();
	_proj = make_shared<MatrixBuffer>();

	_world->Update_Resource();
	_view->Update_Resource();

	XMMATRIX temp = XMMatrixOrthographicOffCenterLH(0,WIN_WIDTH,0,WIN_HEIGHT, 0.0f, 1.0f);

	_proj->SetData(temp);
	_proj->Update_Resource();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	// 키보드 입력 처리
	if (GetAsyncKeyState('W') & 0x8000) // W 키
		Move(0.0f, 0.003f, 0.0f); // 위로 이동
	if (GetAsyncKeyState('S') & 0x8000) // S 키
		Move(0.0f, -0.003f, 0.0f); // 아래로 이동
	if (GetAsyncKeyState('A') & 0x8000) // A 키
		Move(-0.003f, 0.0f, 0.0f); // 왼쪽으로 이동
	if (GetAsyncKeyState('D') & 0x8000) // D 키
		Move(0.003f, 0.0f, 0.0f); // 오른쪽으로 이동
	if (GetAsyncKeyState('Q') & 0x8000) // Q 키
	{
		_angle -= XMConvertToRadians(0.1f); // 반시계 방향으로 회전
		if (_angle < 0.0f)
			_angle += XM_2PI;
	}
	if (GetAsyncKeyState('R') & 0x8000) // R 키
	{
		_angle += XMConvertToRadians(0.1f); // 시계 방향으로 회전
		if (_angle >= XM_2PI)
			_angle -= XM_2PI;
	}
	if (GetAsyncKeyState('F') & 0x8000) // F 키
		_scale += 0.0001f; // 확대
	if (GetAsyncKeyState('G') & 0x8000) // G 키
		_scale -= 0.0001f; // 축소

	// 정점 = (SRT = world * view, porj)
	//XMMatrixScaling()
	//XMMatrixRotationZ() 
	
	// 월드 행렬
	XMMATRIX translate = XMMatrixTranslation(_x, _y, 0);
	XMMATRIX scaling = XMMatrixScaling(_scale, _scale, 1.0f);
	XMMATRIX rotation = XMMatrixRotationZ(_angle);
	

	XMMATRIX worldMatrix = scaling * rotation * translate;

	_world->SetData(worldMatrix);
	_world->Update_Resource();

	_quad->Update();
}

void TutorialScene::Render()
{
	_world->SetVS_Buffer(0);
	_view->SetVS_Buffer(1);
	_proj->SetVS_Buffer(2);

	_quad->Render();
}