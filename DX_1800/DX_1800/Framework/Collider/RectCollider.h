#pragma once
#include "../../Types.h"
class RectCollider : public Collider
{
public:
	RectCollider(Vector2 size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	void CreateVertices();
	void CreateData();

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

	float Left() { return _transform->GetWorldPos().x - (_size * 0.5f).x; }
	float Right() { return _transform->GetWorldPos().x + (_size * 0.5f).x; }
	float Bottom() { return _transform->GetWorldPos().y - (_size * 0.5f).y; }
	float Top() { return _transform->GetWorldPos().y + (_size * 0.5f).y; }

	shared_ptr<Transform> GetTransform() { return _transform; }


private:
	Vector2 _size;

};

