#pragma once
class DunBullet
{
public:
	DunBullet();
	~DunBullet();

	void Update();
	void Render();

	void SetPos(Vector2 pos) { _pos = pos; }
	void SetDir(Vector2 dir) { _dir = dir.NorMalVector2(); }

	void Fire(Vector2 stratPos, Vector2 dir);

	void InPut();

	bool IsActive = false;

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;

	Vector2 _pos = Vector2();
	Vector2 _dir = Vector2();
	float _speed = 500.0f;
	int _damage = 1;
	bool _isActive = false;
};

