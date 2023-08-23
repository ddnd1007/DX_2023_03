#pragma once
class Item
{
enum class ItemInfo
{
	NAME,
	NONE

};
public:
	Item();
	~Item();

	void Update();
	void Render();



private:
	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _trans;
};



