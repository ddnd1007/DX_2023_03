#include "framework.h"
#include "MapleInventory.h"
#include "InventorySlot.h"

MapleInventory::MapleInventory()
{
	//_quad = make_shared<Quad>();
	_slot = make_shared<RectCollider>(Vector2(Vector2(20,20)));
	_trans = make_shared<Transform>();
	
	/*Vector2 offset = Vector2(100, 100);*/

	//_slot.resize(_inventoryY);
	//for (int y = 0; y < _inventoryY; y++)
	//{
	//	_slot[y].resize(_inventoryY);

	//	for (int x = 0; x < _inventoryX; x++)
	//	{
	//		shared_ptr<RectCollider> inventory = make_shared<RectCollider>();
	//		inventory->GetTransform()->SetPosition(offset + (Vector2(5 * x, 10 * y)));

	//		_slot[y][x] = inventory;
	//	}
	//}
	
}

MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	PrintInventory();
	_trans->Update();
	for (auto inventoryArr : _slot)
	{
		for (auto _slot : inventoryArr)
			_slot->Update();
	}
}

void MapleInventory::Render()
{
	_trans->SetWorldBuffer(0);
	for (auto inventoryArr : _slot)
	{
		for (auto _slot : inventoryArr)
			_slot->Render();
	}
}

void MapleInventory::PrintInventory()
{
	Vector2 offset = Vector2(100, 100);

	_slot.resize(_inventoryY);
	for (int y = 0; y < _inventoryY; y++)
	{
		_slot[y].resize(_inventoryY);

		for (int x = 0; x < _inventoryX; x++)
		{
			shared_ptr<RectCollider> inventory = make_shared<RectCollider>();
			inventory->GetTransform()->SetPosition(offset + (Vector2(x, y)));

			_slot[y][x] = inventory;
		}
	}
}


