#pragma once
#include "../../../Types.h"
class DunPlayer
{
public:
	DunPlayer();
	~DunPlayer();

	void Update();
	void Render();

	void Fire();
	shared_ptr<DunBullet> SetBullet();

	void Move();

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	void AddVector2(Vector2 pos) { _quad->GetTransform()->AddVector2(pos); }
  
private:
	shared_ptr<Quad> _quad;
	shared_ptr<Quad> _bow;
	shared_ptr<Transform> _bowAngle;
	shared_ptr<Transform> _muzzle;
	shared_ptr<DunBullet> _bullet;
	vector<shared_ptr<DunBullet>> _bullets;

	Vector2 _pos = CENTER;
	float _speed = 0.01f;

	bool _mousePress = false;
	bool _mouseUp = true;
};

