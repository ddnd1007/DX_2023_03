#include "framework.h"
#include "MapleInventory.h"
#include "EquipmentInven.h"
#include "item.h"

MapleInventory::MapleInventory()
{
	_quad = make_shared<Quad>(L"Resource/Maple/UI/inventory.png");
	_trans = make_shared<Transform>();
	_col = make_shared<RectCollider>(Vector2(_quad->GetImageSize().x, -30.0f));
	_dragBar = make_shared<RectCollider>(Vector2(_quad->GetImageSize().x, 20.0f));
	oldpos = make_shared<Transform>();
	oldpos->SetParent(_col->GetTransform());

	_trans->SetParent(_col->GetTransform());

	_col->GetTransform()->SetPosition(Vector2(300.0f, 100.0f));
	_dragBar->GetTransform()->SetParent(_col->GetTransform());
	_dragBar->GetTransform()->SetPosition({ 0.0f, 200.0f });

	_items.resize(128);
	_haven.resize(128);
	_equipment.resize(4);
	for (int i = 0; i < _equipment.size(); i++)
	{
		_equipment[i] = make_shared<EquipmentInven>();
		_equipment[i]->_col->GetTransform()->SetParent(_col->GetTransform());
	}


	OpenInventory();
}
MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	_col->Update();
	_quad->Update();
	_trans->Update();
	_dragBar->Update();

	Drag();
	SetEquipment();

	for (auto itemarr : _items)
	{
		for (auto item : itemarr)
		{
			item->Update();
			item->drag = false;
		}
	}
	for (auto havenarr : _haven)
	{
		for (auto haven : havenarr)
		{
			haven->Update();
		}
	}
}

void MapleInventory::Render()
{
	if (active == true)
	{
		_trans->SetWorldBuffer(0);
		_col->Render();
		_quad->Render();
		_dragBar->Render();


		for (auto itemarr : _items)
		{
			for (auto item : itemarr)
			{
				item->Render();
			}
		}

		for (auto havenarr : _haven)
		{
			for (auto haven : havenarr)
			{
				haven->Render();
			}
		}
	}
}

void MapleInventory::Drag()
{
	if (_dragBar->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_LBUTTON))
	{
		_col->GetTransform()->SetPosition({ W_MOUSE_POS.x, W_MOUSE_POS.y - 200.0f });
	}
}

void MapleInventory::OpenInventory()
{
	for (int i = 0; i < _equipment.size(); i++)
	{
		_equipment[i] = make_shared<EquipmentInven>();
		_equipment[i]->_col->GetTransform()->SetParent(_col->GetTransform());
	}

	for (int y = 0; y < slotY; y++)
	{
		_items.reserve(128);

		for (int x = 0; x < slotX; x++)
		{
			shared_ptr<Item> item = make_shared<Item>();
			item->_col->GetTransform()->SetParent(_col->GetTransform());

			item->_col->GetTransform()->SetPosition(Vector2((x * 36) - 270, (y * 35) - 130));

			_items[y].push_back(item);
		}
	}
	for (int y = 0; y < slotY; y++)
	{
		_haven.reserve(128);

		for (int x = 0; x < slotX; x++)
		{
			shared_ptr<Item> item = make_shared<Item>();
			item->_col->GetTransform()->SetParent(_col->GetTransform());

			item->_col->GetTransform()->SetPosition(Vector2((x * 36) - 270, (y * 35) - 130));

			_haven[y].push_back(item);
		}
	}
}

void MapleInventory::SetEquipment()
{
	for (auto havenarr : _haven)
	{
		for (auto haven : havenarr)
		{
			if (haven->_col->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_RBUTTON))
			{
				if (haven->GetInfo() == Item::HAT)
				{
					if (haven->used == false)
					{
						haven->SetOldPos(haven->_col->GetTransform()->GetPos());
						haven->used = true;
						haven->_col->GetTransform()->SetPosition(_equipment[0]->_col->GetTransform()->GetPos());
					}
					else if (haven->used == true)
					{
						haven->used = false;
						haven->_col->GetTransform()->SetPosition(haven->GetOldPos());
					}
				}
				if (haven->GetInfo() == Item::TOP)
				{
					if (haven->used == false)
					{
						haven->SetOldPos(haven->_col->GetTransform()->GetPos());
						haven->used = true;
						haven->_col->GetTransform()->SetPosition(_equipment[1]->_col->GetTransform()->GetPos());
					}
					else if (haven->used == true)
					{
						haven->used = false;
						haven->_col->GetTransform()->SetPosition(haven->GetOldPos());
					}
				}
				if (haven->GetInfo() == Item::PANTS)
				{
					if (haven->used == false)
					{
						haven->SetOldPos(haven->_col->GetTransform()->GetPos());
						haven->used = true;
						haven->_col->GetTransform()->SetPosition(_equipment[2]->_col->GetTransform()->GetPos());
					}
					else if (haven->used == true)
					{
						haven->used = false;
						haven->_col->GetTransform()->SetPosition(haven->GetOldPos());
					}

				}
				if (haven->GetInfo() == Item::BOW)
				{
					if (haven->used == false)
					{
						haven->SetOldPos(haven->_col->GetTransform()->GetPos());
						haven->used = true;
						haven->_col->GetTransform()->SetPosition(_equipment[3]->_col->GetTransform()->GetPos());
					}
					else if (haven->used == true)
					{
						haven->used = false;
						haven->_col->GetTransform()->SetPosition(haven->GetOldPos());
					}
				}
			}
		}
	}
}

void MapleInventory::EquipItem(shared_ptr<Item> item, shared_ptr<EquipmentInven> slot)
{
	if (item->used)
	{
		slot->_col->GetTransform()->SetPosition(item->GetOldPos());
		item->used = false;
	}
	else
	{
		slot->_col->GetTransform()->SetPosition(item->_col->GetTransform()->GetPos());
		item->used = true;
	}

}

void MapleInventory::GetItem()
{
	int value = 0;

	for (auto havenarr : _haven)
	{
		for (auto haven : havenarr)
		{
			for (auto equipment : _equipment)
			{
				if (haven->_col->GetTransform()->GetPos() == equipment->_col->GetTransform()->GetPos())
				{
					haven->used = true;
				}
			}
		}
	}
}
























