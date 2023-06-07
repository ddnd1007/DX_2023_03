#pragma once
class DunBullet
{
public:
	DunBullet();
	~DunBullet();

	void Update();
	void Render();

	void SetPos(const Vector2& pos) { _pos = pos; }
	void SetDir(Vector2 dir) { _dir = dir.NorMalVector2(); }

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive; }

	shared_ptr<Transform> GetTrans() { return _quad->GetTransform(); }

	

private:
	shared_ptr<Quad> _quad;
	Vector2 _dir = Vector2();
	Vector2 _pos = Vector2();
	float _speed = 0.06f;
	bool _isActive = false;
};

