#pragma once
class MapleInventory
{
public:
	MapleInventory();
	~MapleInventory();

	void Update();
	void Render();

	void InventoryView();

	void Inventory();

	
private:
	vector<vector<shared_ptr<RectCollider>>> _rectCol;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	const UINT _inventoryX = 5;
	const UINT _inventoryY = 10;
	
};

