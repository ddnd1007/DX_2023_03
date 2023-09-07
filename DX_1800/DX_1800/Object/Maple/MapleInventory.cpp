#include "framework.h"
#include "MapleInventory.h"
#include "Slot.h"

Vector2 offset(50, 50);

MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
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

void MapleInventory::InitializeSlots()
{
	_slot.resize(slotY);
	for (int y = 0; y < slotY; y++)
	{
		_slot[y].resize(slotX);

		for (int x = 0; x < slotX; x++)
		{
			shared_ptr<Slot> slot = make_shared<Slot>();
			slot->SetPosition(offset + Vector2(40*x,40*y));
			slot->SetType(Slot::SlotType::NONE);

			_slot[y][x] = slot;
		}
	}
}

void MapleInventory::ToggleInventory()
{
	if (KEY_PRESS('I')) {
		if (inventoryVisible) {
			CloseInventory(); // 인벤토리 숨기기
			inventoryVisible = false;
		}
		else {
			InitializeSlots(); // 인벤토리 표시하기
			inventoryVisible = true;
		}
	}
}

void MapleInventory::ClearSlots()
{
	for (int y = 0; y < slotY; y++)
	{
		for (int x = 0; x < slotX; x++)
		{
			_slot[y][x].reset(new Slot());
			_slot[y][x]->SetType(Slot::SlotType::NONE);
		}
	}
}

void MapleInventory::CloseInventory()
{
	ClearSlots();
	inventoryVisible = false;
}




	








