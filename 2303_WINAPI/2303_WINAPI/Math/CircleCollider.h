#pragma once
class CircleCollider
{
public:
	CircleCollider() {}
	CircleCollider(float radius, Vector2 center);
	~CircleCollider() {}

	void Update();
	void Render(HDC hdc);

	void SetCenter(Vector2 pos) { _center = pos; }
	const Vector2& GetCenter() { return _center; }

	void SetRadius(float radius) { _radius = radius; }
	float GetRadius() { return _radius; }

private:
	float _radius = 0.0f;
	Vector2 _center = { 0.0f,0.0f };
};

