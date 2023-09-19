#pragma once
class EquipmentInven
{
	friend class PlayerManager;
public:

	EquipmentInven();
	~EquipmentInven();

	void Update();
	void Render();

	void Drag();
	void OpenInventory();

	int GetItem();
	void Equipment();
	void SetEquipment(shared_ptr<class Item> item);
	void GetPosition();

	bool itemDrag = false;
	bool active = false;

public:
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _dragBar;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;

	shared_ptr<Transform> oldpos;

	vector<shared_ptr<class Item>> _haven;
	vector<shared_ptr<class Item>> _item;
	vector<shared_ptr<class Item>> _equipment;

};

