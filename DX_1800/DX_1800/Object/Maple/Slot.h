#pragma once
class Slot
{
public:
	enum class SlotType
	{
		FULL,
		NONE
	};

	Slot();
	~Slot();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetType(Slot::SlotType type) { _type = type; }
	Slot::SlotType GetType() { return _type; }

private:
	SlotType _type = SlotType::NONE;

	shared_ptr<RectCollider> _col;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;
};



