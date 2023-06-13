#pragma once
class DunBullet
{
public:
	DunBullet();
	~DunBullet();

	void Update();
	void Render();

	void Attack(shared_ptr<class DunMonster> victim);

	void SetPos(Vector2 pos) { _pos = pos; }
	void SetDir(Vector2 dir) { _dir = dir.NorMalVector2(); }

	void SetActive(bool active) { _isActive = active; }
	bool IsActive() { return _isActive; }

	shared_ptr<Transform> GetQuadTransform() { return _quad->GetTransform(); }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

private:
	shared_ptr<CircleCollider> _col;
	shared_ptr<Quad> _quad;

	Vector2 _pos = Vector2();
	Vector2 _dir = Vector2();
	float _speed = 550.0f;
	int _damage = 1;

	bool _isActive = false;

};

