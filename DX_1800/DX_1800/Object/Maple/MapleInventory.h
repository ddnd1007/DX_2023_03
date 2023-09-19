#pragma once
class MapleInventory
{
	friend class PlayerManager;
public:
	MapleInventory();
	~MapleInventory();

	void Update();
	void Render();

	void Drag();
	void OpenInventory();
	void SetEquipment();
	void EquipItem(shared_ptr<Item> item, shared_ptr<class EquipmentInven> slot);
	void GetItem();

	bool itemDrag = false;
	bool active = false;


public:
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _dragBar;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	vector<vector<shared_ptr<class Item>>> _items;
	vector<vector<shared_ptr<class Item>>> _haven;

	vector<shared_ptr<class EquipmentInven>> _equipment;


	shared_ptr<Transform> oldpos;

	UINT slotX = 16;
	UINT slotY = 8;
};

