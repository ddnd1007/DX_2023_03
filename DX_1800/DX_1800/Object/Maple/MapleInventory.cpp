#include "framework.h"
#include "MapleInventory.h"
#include "item.h"

MapleInventory::MapleInventory()
{
	_quad = make_shared<Quad>(L"Resource/Maple/UI/inventory.png");
	_trans = make_shared<Transform>();
	_col = make_shared<RectCollider>(_quad->GetImageSize());
	_dragBar = make_shared<RectCollider>(Vector2(_quad->GetImageSize().x, 10.0f));

	_trans->SetParent(_col->GetTransform());

	_col->GetTransform()->SetPosition(Vector2(0.0f, 0.0f));

	_dragBar->GetTransform()->SetParent(_col->GetTransform());
	_dragBar->GetTransform()->SetPosition({ 0.0f, 200.0f });

	_items.resize(128);
	
	OpenInventory();
}
MapleInventory::~MapleInventory()
{
}

void MapleInventory::Update()
{
	_col->Update();
	_quad->Update();
	_dragBar->Update();
	_trans->Update();

	Drag();

	for (auto itemarr : _items)
	{
		for (auto item : itemarr)
		{
			item->Update();
			item->drag = false;
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
	for (int y = 0; y < slotY; y++)
	{
		_items.reserve(128);

		for (int x = 0; x < slotX; x++)
		{
			shared_ptr<Item> item = make_shared<Item>();
			item->_col->GetTransform()->SetParent(_col->GetTransform());

			item->_col->GetTransform()->SetPosition(Vector2(x * 30, y* 30));

			_items[y].push_back(item);
		}
	}
}





	








