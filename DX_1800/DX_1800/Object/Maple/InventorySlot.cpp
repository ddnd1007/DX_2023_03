#include "framework.h"
#include "InventorySlot.h"

InventorySlot::InventorySlot()
{
	_rectCol = make_shared<RectCollider>(Vector2(), Vector2(20, 20));
}

InventorySlot::~InventorySlot()
{
	
}

void InventorySlot::Update()
{
	_rectCol->Update();
}

void InventorySlot::Render()
{
	_rectCol->Render();
}
