#pragma once
class DunPlayer
{
public:
	DunPlayer();
	~DunPlayer();

	void Update();
	void Render();

	void InPut();
	void Move();

	void SetRotation(float speed) { _rotationSpeed = speed; }
	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	void AddVector2(Vector2 pos) { _quad->GetTransform()->AddVector2(pos); }

	vector<shared_ptr<class DunBullet>>& GetBullets() { return _bullets; }


private:
	Vector2 _pos;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _trans;
	shared_ptr<Transform> _bowSlot;
	shared_ptr<CircleCollider> _bible1;
	shared_ptr<CircleCollider> _bible2;
	shared_ptr<CircleCollider> _bible3;

	shared_ptr<Quad> _bowQuad;

	vector<shared_ptr<class DunBullet>> _bullets;

	shared_ptr<Transform> _orbit;

	float _speed = 0.1f;

	float _rotationSpeed = 0.0001f;
};

