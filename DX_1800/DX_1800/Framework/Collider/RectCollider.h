#pragma once
#include "../../Types.h"
class RectCollider : public Collider
{
public:
	struct AABB_info
	{
		float left = 0;
		float top = 0;
		float right = 0;
		float bottom = 0;
	};
	RectCollider(Vector2 size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	void CreateVertices();
	void CreateData();

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

	AABB_info GetAABB_Info();
	




private:
	Vector2 _size;

};

