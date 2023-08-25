#include "framework.h"
#include "Slot.h"

Slot::Slot()
{
	//_quad = make_shared<Quad>(L"");
	_col = make_shared<RectCollider>(Vector2(350, 350));
	_trans = make_shared<Transform>();
}

Slot::~Slot()
{
}

void Slot::Update()
{
	//_quad->Update();
	_col->Update();
	_trans->Update();
}

void Slot::Render()
{
	_trans->SetWorldBuffer(0);
	_col->Render();
	//_quad->Render();
}
