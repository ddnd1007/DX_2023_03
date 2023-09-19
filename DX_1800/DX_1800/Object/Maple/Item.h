#pragma once
class Item
{
	friend class MapleInventory;
	friend class EquipmentInventory;

public:

	enum ItemInfo
	{
		NONE,
		BOW,
		HAT,
		TOP,
		PANTS
	};

	Item();
	Item(wstring path, ItemInfo info = NONE);
	~Item();

	void Update();
	void Render();

	ItemInfo GetInfo() { return info; }
	void SetItemInfo(ItemInfo Info) { info = Info; }
	void SetQuad(wstring path);

	bool colision(Vector2 mouse, shared_ptr<RectCollider> rect);
	bool used = false;
	bool drag = false;

	Vector2 GetOldPos() { return  oldPos; }
	void SetOldPos(Vector2 pos) { oldPos = pos; }



public:
	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _trans;

	Vector2 oldPos = { 0.0f,0.0f };

	ItemInfo info = NONE;


};



