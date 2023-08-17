#include "framework.h"
#include "InventorySlot.h"

InventorySlot::InventorySlot()
{
	_rectCol = make_shared<RectCollider>(Vector2(20, 20));
	_trans = make_shared<Transform>();
	_trans->SetParent(_rectCol->GetTransform());
}

InventorySlot::~InventorySlot()
{
	
}

void InventorySlot::Update()
{
	_rectCol->Update();
	_trans->Update();
}

void InventorySlot::Render()
{
	_trans->SetWorldBuffer(0);
	_rectCol->Render();
}
