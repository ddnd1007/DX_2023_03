#include "framework.h"
#include "MapleInventory.h"

MapleInventory::MapleInventory()
{
	//_quad = make_shared<Quad>();
	_trans = make_shared<Transform>();

	Vector2 offset = Vector2(100, 100);

	_rectCol.resize(_inventoryY);
	for (int y = 0; y < _inventoryY; y++)
	{
		_rectCol[y].resize(_inventoryY);

		for (int x = 0; x < _inventoryX; x++)
		{
			shared_ptr<RectCollider> inventory = make_shared<RectCollider>();
			inventory->GetTransform()->SetPosition(offset + Vector2((Vector2(5 * x, 10 * y))));

			_rectCol[y][x] = inventory;
		}
	}

}

MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	for (auto inventoryArr : _rectCol)
	{
		for (auto inventory : inventoryArr)
			inventory->Update();
	}
}

void MapleInventory::Render()
{
	for (auto inventoryArr : _rectCol)
	{
		for (auto inventory : inventoryArr)
			inventory->Render();
	}
}

void MapleInventory::InventoryView()
{
	if (KEY_PRESS('I'))
	{
		Vector2 offset = Vector2(100, 100);

		_rectCol.resize(_inventoryY);
		for (int y = 0; y < _inventoryY; y++)
		{
			_rectCol[y].resize(_inventoryY);

			for (int x = 0; x < _inventoryX; x++)
			{
				shared_ptr<RectCollider> inventory = make_shared<RectCollider>();
				inventory->GetTransform()->SetPosition(offset + Vector2((Vector2(x, y))));

				_rectCol[y].push_back(inventory);
			}
		}
	}
}

