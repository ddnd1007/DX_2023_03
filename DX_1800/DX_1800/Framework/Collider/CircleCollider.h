#pragma once
class CircleCollider : public enable_shared_from_this<CircleCollider>, public Collider
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider();

	virtual void Update() override;
	virtual  void Render() override;

	void CreateVertices();
	void CreateData();

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	float GetRadius() { return _radius; }

	float Left() { return _transform->GetWorldPos().x - _radius; }
	float Right() { return _transform->GetWorldPos().x + _radius; }
	float Bottom() { return _transform->GetWorldPos().y - _radius; }
	float Top() { return _transform->GetWorldPos().y + _radius; }

private:
	float _radius;
};

