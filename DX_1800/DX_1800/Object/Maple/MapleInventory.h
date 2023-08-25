#pragma once
class MapleInventory
{
public:
	MapleInventory();
	~MapleInventory();

	void Update();
	void Render();

	void PrintInventory();

private:
	vector<vector<shared_ptr<class Slot>>> _slot;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	UINT slotX = 5;
	UINT slotY = 10;
};

