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

	shared_ptr<Transform> GetTransform() { return _trans; }

	void Update();
	void Render();

	

private:
	SlotType _type = SlotType::NONE;
	shared_ptr<RectCollider> _rectCol;
	shared_ptr<Transform> _trans;

};

