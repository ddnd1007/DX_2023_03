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

	
	bool itemDrag = false;
	bool active = false;
	

private:
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _dragBar;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	vector<vector<shared_ptr<class Item>>> _items;
	//vector<vector<shared_ptr<class Item>>> _haven;
	
	UINT slotX = 16;
	UINT slotY = 8;
};

