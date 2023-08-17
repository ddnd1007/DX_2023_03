#pragma once
class MapleInventory
{
	/*struct Item
	{
		std::string name;
		int quantity;

		Item(const std::string& n, int q) : name(n), quantity(q) {}
	};*/
public:
	MapleInventory();
	~MapleInventory();

	void Update();
	void Render();

	void PrintInventory();

private:
	vector<vector<shared_ptr<RectCollider>>> _slot;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	const UINT _inventoryX = 5;
	const UINT _inventoryY = 10;
	
};

