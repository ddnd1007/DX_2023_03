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
	// Ű���� �Է� ó��
	if (GetAsyncKeyState('W') & 0x8000) // W Ű
		Move(0.0f, 0.003f, 0.0f); // ���� �̵�
	if (GetAsyncKeyState('S') & 0x8000) // S Ű
		Move(0.0f, -0.003f, 0.0f); // �Ʒ��� �̵�
	if (GetAsyncKeyState('A') & 0x8000) // A Ű
		Move(-0.003f, 0.0f, 0.0f); // �������� �̵�
	if (GetAsyncKeyState('D') & 0x8000) // D Ű
		Move(0.003f, 0.0f, 0.0f); // ���������� �̵�
	if (GetAsyncKeyState('Q') & 0x8000) // Q Ű
	{
		_angle -= XMConvertToRadians(0.1f); // �ݽð� �������� ȸ��
		if (_angle < 0.0f)
			_angle += XM_2PI;
	}
	if (GetAsyncKeyState('R') & 0x8000) // R Ű
	{
		_angle += XMConvertToRadians(0.1f); // �ð� �������� ȸ��
		if (_angle >= XM_2PI)
			_angle -= XM_2PI;
	}
	if (GetAsyncKeyState('F') & 0x8000) // F Ű
		_scale += 0.0001f; // Ȯ��
	if (GetAsyncKeyState('G') & 0x8000) // G Ű
		_scale -= 0.0001f; // ���

	// ���� = (SRT = world * view, porj)
	//XMMatrixScaling()
	//XMMatrixRotationZ() 
	
	// ���� ���
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