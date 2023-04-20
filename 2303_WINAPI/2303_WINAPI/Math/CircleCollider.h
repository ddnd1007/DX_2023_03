#pragma once
class CircleCollider
{
public:
	CircleCollider();
	CircleCollider(float radius, Vector2 center);
	~CircleCollider();

	void Update();
	void Render(HDC);

private:
	// ¸â¹öº¯¼ö?
	float _radius = 0.0f;
	Vector2 _center = { 0.0f,0.0f };
};

