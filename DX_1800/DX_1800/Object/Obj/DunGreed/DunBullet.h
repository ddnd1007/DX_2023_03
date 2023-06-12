#pragma once
class DunBullet
{
public:
	DunBullet();
	~DunBullet();


	void Update();
	void Render();

	void Attack(shared_ptr<DunBoss> victim);

	void SetPos(Vector2 pos) { _pos = pos; }
	void SetDir(Vector2 dir) { _dir = dir.NorMalVector2(); }

	void SetActive(bool active) { _isActive = active; }
	bool IsActive() { return _isActive; }

	shared_ptr<Transform> GetTrans() { return _quad->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetColliderTransform() { return _collider->GetTransform(); }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _collider;

	Vector2 _pos = Vector2();
	Vector2 _dir = Vector2();
	float _speed = 0.1f;
	int _damage = 1;
	bool _isActive = false;
};

