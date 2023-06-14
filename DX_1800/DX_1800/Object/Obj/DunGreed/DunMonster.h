#pragma once
class DunMonster
{
public:
	DunMonster();
	~DunMonster();

	void Update();
	void Render();
	void SetDir(Vector2 pos);

	void TakeDamage(int damage);

	bool IsDead() { return _hp <= 0; }
	bool IsDamaged() { return _isDamaged; }

	int& GetHp() { return _hp; }
	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

private:
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _quadTrans;
	shared_ptr<Quad> _quad;

	int _hp = 10;
	bool _isDamaged = false;

	float _curTime = 0.0f;
	float _damageTime = 0.2f;

	Vector2 _dir = Vector2();
	float _speed = 50.0f;
};
