#pragma once
class MapleInventory
{
public:
	MapleInventory() { _trans = make_shared<Transform>(); };
	~MapleInventory();

	void Update();
	void Render();

	void InitializeSlots();
	void ToggleInventory();
	void ClearSlots();
	void CloseInventory();

private:
	vector<vector<shared_ptr<class Slot>>> _slot;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	UINT slotX = 5;
	UINT slotY = 10;

	bool inventoryVisible = false;
};

