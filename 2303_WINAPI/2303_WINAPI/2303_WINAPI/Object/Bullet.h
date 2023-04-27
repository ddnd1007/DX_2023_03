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

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive; }

private:
	bool _isActive = false;

	Vector2 _pos = Vector2();
	Vector2 _direction = Vector2();
	float _speed =7.0f;

	shared_ptr<CircleCollider> _circle;

	
};

