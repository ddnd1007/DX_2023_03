#pragma once
class InventorySlot
{
public:
	enum class SlotType
	{
		ABLE,
		DISABLE,
		NONE
	};
	InventorySlot();
	~InventorySlot();

	void Update();
	void Render();

	

private:
	SlotType _type = SlotType::NONE;
	shared_ptr<RectCollider> _rectCol;

};

