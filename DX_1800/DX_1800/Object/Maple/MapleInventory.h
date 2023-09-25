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
	void Equipment();
	void GetItem();

	bool itemDrag = false;
	bool active = false;


public:
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _col2;
	shared_ptr<RectCollider> _dragBar;
	shared_ptr<RectCollider> _dragBar2;
	shared_ptr<Quad> _quad;
	shared_ptr<Quad> _quad2;
	shared_ptr<Transform> _trans;
	shared_ptr<Transform> _trans2;

	vector<vector<shared_ptr<class Item>>> _items;
	vector<vector<shared_ptr<class Item>>> _haven;

	vector<shared_ptr<class Item>> _equipment;


	shared_ptr<Transform> oldpos;

	UINT slotX = 16;
	UINT slotY = 8;

	
};

