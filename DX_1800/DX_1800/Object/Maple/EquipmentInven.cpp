#include "framework.h"
#include "EquipmentInven.h"
#include "item.h"

EquipmentInven::EquipmentInven()
{
	_quad = make_shared<Quad>(L"Resource/Maple/UI/equipment.png");
	_trans = make_shared<Transform>();
	_col = make_shared<RectCollider>(Vector2(_quad->GetImageSize().x, -30.0f));
	_dragBar = make_shared<RectCollider>(Vector2(_quad->GetImageSize()));

	oldpos = make_shared<Transform>();
	oldpos->SetParent(_col->GetTransform());

	_trans->SetParent(_col->GetTransform());

	_col->GetTransform()->SetPosition(Vector2(0.0f, 0.0f));

	_dragBar->GetTransform()->SetParent(_col->GetTransform());
	_dragBar->GetTransform()->SetPosition({ 0.0f, 100.0f });

	_equipment.resize(4);
	_haven.resize(4);
	_item.resize(4);

	OpenInventory();
}

EquipmentInven::~EquipmentInven()
{
}

void EquipmentInven::Update()
{
	Equipment();
	_col->Update();
	_quad->Update();
	_dragBar->Update();
	_trans->Update();
	Drag();
	GetItem();

	for (int i = 0; i < _equipment.size(); i++)
	{
		_equipment[i]->Update();
	}
	for (int i = 0; i < _item.size(); i++)
	{
		_item[i]->Update();
		_item[i]->drag = false;
	}
	for (int i = 0; i < _haven.size(); i++)
	{
		_haven[i]->Update();
	}

}

void EquipmentInven::Render()
{
	if (active == true)
	{
		_trans->SetWorldBuffer(0);
		_col->Render();
		_quad->Render();
		_dragBar->Render();

		for (int i = 0; i < _equipment.size(); i++)
		{
			_equipment[i]->Render();
		}

		for (int i = 0; i < _equipment.size(); i++)
		{
			_equipment[i]->Update();
		}
		for (int i = 0; i < _item.size(); i++)
		{
			_item[i]->Update();
		}
		for (int i = 0; i < _haven.size(); i++)
		{
			_haven[i]->Update();
		}
	}
}

void EquipmentInven::Drag()
{
	if (_dragBar->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_LBUTTON))
	{
		_col->GetTransform()->SetPosition({ W_MOUSE_POS.x, W_MOUSE_POS.y - 200.0f });
	}
}

void EquipmentInven::Equipment()
{
	_equipment[0]->_col->GetTransform()->SetPosition(Vector2(-32.0f, 102.0f));
	_equipment[0]->SetItemInfo(Item::HAT);
	_equipment[1]->_col->GetTransform()->SetPosition(Vector2(-32.0f, 2.0f));
	_equipment[1]->SetItemInfo(Item::TOP);
	_equipment[2]->_col->GetTransform()->SetPosition(Vector2(-32.0f, -32.0f));
	_equipment[2]->SetItemInfo(Item::PANTS);
	_equipment[3]->_col->GetTransform()->SetPosition(Vector2(34.0f, 2.0f));
	_equipment[3]->SetItemInfo(Item::BOW);
}

void EquipmentInven::OpenInventory()
{
	for (int i = 0; i < _equipment.size(); i++)
	{
		_equipment[i] = make_shared<Item>();
		_equipment[i]->_col->GetTransform()->SetParent(_col->GetTransform());
	}
	for (int i = 0; i < _item.size(); i++)
	{
		_item[i] = make_shared<Item>();
		_item[i]->_col->GetTransform()->SetParent(_col->GetTransform());
	}
	for (int i = 0; i < _haven.size(); i++)
	{
		_haven[i] = make_shared<Item>();
		_haven[i]->_col->GetTransform()->SetParent(_col->GetTransform());
	}
}

//void EquipmentInven::SetEquipment(shared_ptr<class Item> item)
//{
//	for (auto haven : _haven)
//	{
//		if (haven->_col->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_RBUTTON))
//		{
//			if (haven->GetInfo() == Item::HAT)
//			{
//				if (haven->used == false)
//				{
//					haven->SetOldPos(haven->_col->GetTransform()->GetPos());
//					haven->used = true;
//					haven->_col->GetTransform()->SetPosition(_equipment[0]->_col->GetTransform()->GetPos());
//				}
//			}
//			if (haven->GetInfo() == Item::TOP)
//			{
//				if (haven->used == false)
//				{
//					haven->SetOldPos(haven->_col->GetTransform()->GetPos());
//					haven->used = true;
//					haven->_col->GetTransform()->SetPosition(_equipment[1]->_col->GetTransform()->GetPos());
//				}
//			}
//			if (haven->GetInfo() == Item::PANTS)
//			{
//				if (haven->used == false)
//				{
//					haven->SetOldPos(haven->_col->GetTransform()->GetPos());
//					haven->used = true;
//					haven->_col->GetTransform()->SetPosition(_equipment[2]->_col->GetTransform()->GetPos());
//				}
//			}
//			if (haven->GetInfo() == Item::BOW)
//			{
//				if (haven->used == false)
//				{
//					haven->SetOldPos(haven->_col->GetTransform()->GetPos());
//					haven->used = true;
//					haven->_col->GetTransform()->SetPosition(_equipment[3]->_col->GetTransform()->GetPos());
//				}
//			}
//		}
//	}
//}

int EquipmentInven::GetItem()
{
	int value = 0;

	for (int i = 0; i < _haven.size(); i++)
	{
		for (auto equipment : _equipment)
		{
			if (_haven[i]->_col->GetTransform()->GetPos() == equipment->_col->GetTransform()->GetPos())
			{
				_haven[i]->used = true;
			}
		}
	}
	return value;
}



















