#include "framework.h"
#include "MapleInventory.h"
#include "Slot.h"

MapleInventory::MapleInventory()
{
	//_quad = make_shared<Quad>(L"");
	_trans = make_shared<Transform>();

	Vector2 offset = Vector2(100, 100);

	_slot.resize(10);
	for (int y = 0; y < slotY; y++)
	{
		_slot[y].reserve(10);
		for (int x = 0; x < slotX; x++)
		{
			shared_ptr<Slot> slot = make_shared<Slot>();
			slot->SetPosition(offset + Vector2(30 * x,30 * y));
			slot->SetType(Slot::SlotType::NONE);	

			_slot[y].push_back(slot);
		}
	}
}

MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	PrintInventory();

	for (auto slotArr : _slot)
	{
		for (auto slot : slotArr)
			slot->Update();
	}
}

void MapleInventory::Render()
{
	for (auto slotArr : _slot)
	{
		for (auto slot : slotArr)
			slot->Render();
	}
}

void MapleInventory::PrintInventory()
{
	if (KEY_PRESS('I'))
	{
		for (int y = 0; y < slotY; y++)
		{
			for (int x = 0; x < slotX; x++)
			{
				_slot[y][x]->SetType(Slot::SlotType::NONE);
				//_slot.push_back(slot)
			}
		}
	}
}

	








