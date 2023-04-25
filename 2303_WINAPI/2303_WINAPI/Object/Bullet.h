#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render(HDC hdc);

	void SetDirection(Vector2 dir) { _direction = dir.NorMalVector2(); }
	void SetPos(const Vector2& pos) { _pos = pos; }

private:
	Vector2 _pos = Vector2();
	Vector2 _direction = Vector2();
	float _speed = 3.0f;

	shared_ptr<CircleCollider> _circle;
};

