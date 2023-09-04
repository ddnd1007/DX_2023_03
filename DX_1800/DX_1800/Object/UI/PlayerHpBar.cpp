#include "framework.h"
#include "PlayerHpBar.h"

PlayerHpBar::PlayerHpBar()
{
	_quadTransform = make_shared<Transform>();
	_quad = make_shared<Quad>(L"Resource/UI/Button.png", Vector2(200, 30));
	_quad->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_buffer = make_shared<BarBuffer>();
	_buffer->_data.ratio = 1.0f;
}

PlayerHpBar::~PlayerHpBar()
{
}

void PlayerHpBar::Update()
{
	_quadTransform->Update();

	_buffer->Update_Resource();
}

void PlayerHpBar::PostRender()
{
	_quadTransform->SetWorldBuffer(0);
	_buffer->SetPS_Buffer(0);
	_quad->Render();
}
