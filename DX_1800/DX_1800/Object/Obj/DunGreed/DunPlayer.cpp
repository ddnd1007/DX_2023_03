#include "framework.h"
#include "DunPlayer.h"

DunPlayer::DunPlayer()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Player.png");
	_bowSlot = make_shared<Transform>();

	_bowQuad = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_bowQuad->GetTransform()->SetParent(_bowSlot);

	_bowQuad->GetTransform()->SetPosition(Vector2(100.0f,0.0f));
	_bowQuad->GetTransform()->SetAngle(-PI * 0.75f);
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::Update()
{
	_quad->Update();

	_bowSlot->SetPosition(_quad->GetTransform()->GetPos());
	_bowSlot->Update();

	_bowQuad->Update();

	Vector2 slotToMousePos = MOUSE_POS - _bowSlot->GetPos();
	float angle = slotToMousePos.Angle();

	_bowSlot->SetAngle(angle);
}

void DunPlayer::Render()
{
	_quad->Render();
	_bowQuad->Render();
}
