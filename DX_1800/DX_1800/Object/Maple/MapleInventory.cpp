#include "framework.h"
#include "MapleInventory.h"
#include "item.h"

MapleInventory::MapleInventory()
{
	_quad = make_shared<Quad>(L"Resource/Maple/UI/inventory.png");
	_trans = make_shared<Transform>();
	_col = make_shared<RectCollider>(Vector2(_quad->GetImageSize().x, -30.0f));
	_dragBar = make_shared<RectCollider>(Vector2(_quad->GetImageSize().x, 20.0f));

	_quad2 = make_shared<Quad>(L"Resource/Maple/UI/equipment.png");
	_trans2 = make_shared<Transform>();
	_col2 = make_shared<RectCollider>(Vector2(_quad2->GetImageSize().x, -30.0f));
	_dragBar2 = make_shared<RectCollider>(Vector2(_quad2->GetImageSize()));

	oldpos = make_shared<Transform>();
	oldpos->SetParent(_col->GetTransform());

	_trans->SetParent(_col->GetTransform());

	_col->GetTransform()->SetPosition(Vector2(300.0f, 100.0f));
	_dragBar->GetTransform()->SetParent(_col->GetTransform());
	_dragBar->GetTransform()->SetPosition({ 0.0f, 200.0f });

	_trans2->SetParent(_col2->GetTransform());

	_col2->GetTransform()->SetParent(_col->GetTransform());
	_col2->GetTransform()->SetPosition(Vector2(400.0f, 0.0f));

	_items.resize(128);
	_haven.resize(128);
	_equipment.resize(4);
	for (int i = 0; i < _equipment.size(); i++)
	{
		_equipment[i] = make_shared<Item>();
		//_equipment[i]->_col->GetTransform()->SetParent(_equipment[i]->_col->GetTransform());
	}

	OpenInventory();
}
MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	Drag();
	Equipment();
	SetEquipment();
	

	_col->Update();
	_quad->Update();
	_trans->Update();
	_dragBar->Update();
	_col2->Update();
	_quad2->Update();
	_trans2->Update();

	for (int i = 0; i < _equipment.size(); i++)
	{
		_equipment[i]->Update();
	}

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
		//_col->Render();
		_quad->Render();
		//_dragBar->Render();

		_trans2->SetWorldBuffer(0);
		//_col2->Render();
		_quad2->Render();
		//_dragBar2->Render();

		for (int i = 0; i < _equipment.size(); i++)
		{
			_equipment[i]->Render();
		}


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
		_equipment[i] = make_shared<Item>();
		_equipment[i]->_col->GetTransform()->GetPos();
	
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

void MapleInventory::Equipment()
{
	_equipment[0]->_col->GetTransform()->SetPosition(Vector2(370.0f, 102.0f));
	_equipment[0]->SetItemInfo(Item::HAT);
	_equipment[1]->_col->GetTransform()->SetPosition(Vector2(370.0f, 2.0f));
	_equipment[1]->SetItemInfo(Item::TOP);
	_equipment[2]->_col->GetTransform()->SetPosition(Vector2(370.0f, -32.0f));
	_equipment[2]->SetItemInfo(Item::PANTS);
	_equipment[3]->_col->GetTransform()->SetPosition(Vector2(470.0f, 2.0f));
	_equipment[3]->SetItemInfo(Item::BOW);
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
				if (equipment->_col->GetTransform()->GetPos() == haven->_col->GetTransform()->GetPos())
				{
					haven->used = true;
				}
			}
		}
	}
}
























