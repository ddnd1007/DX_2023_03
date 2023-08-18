#include "framework.h"
#include "MapleInventory.h"
//#include "InventorySlot.h"

MapleInventory::MapleInventory()
{
	_trans = make_shared<Transform>();

	Vector2 offset = Vector2(100, 100);

	_col.resize(10);
	for (int y = 0; y < _inventoryY; y++)
	{
		_col[y].reserve(10);
		for (int x = 0; x < _inventoryX; x++)
		{
			shared_ptr<RectCollider> slot = make_shared<RectCollider>();
			slot->GetTransform()->SetPosition(offset + Vector2(x, y));
			_col[y].push_back(slot);
		}
	}
  
}

MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	PrintInventory();

	_trans->Update();
	for (auto slotY : _col)
	{
		for (auto slotX : slotY)
			slotX->Update();
	}
}

void MapleInventory::Render()
{
	_trans->SetWorldBuffer(0);
	for (auto slotY : _col)
	{
		for (auto slotX : slotY)
			slotX->Render();
	}
}

void MapleInventory::PrintInventory()
{
	for (int y = 0; y < _inventoryY; y++)
	{
		for (int x = 0; x < _inventoryX; x++)
		{
			_col[y][x]->GetTransform();
		}
	}
}







