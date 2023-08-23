#pragma once
class Slot
{
	enum class SlotType
	{
		FULL,
		NONE
	};

public:
	Slot();
	~Slot();

	void Update();
	void Render();

private:
	shared_ptr<RectCollider> _col;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;
};



