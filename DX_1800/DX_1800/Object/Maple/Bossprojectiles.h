#pragma once
class Bossprojectiles
{
	enum State
	{
		BALL,
		NONE
	};

public:
	Bossprojectiles();
	~Bossprojectiles();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetDirection(Vector2 dir) { _dir = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }

	void SetAction(State state);

	void Attack(shared_ptr<class PlayerManager> victim);
	shared_ptr<CircleCollider> GetCollider() { return _col; }
	Vector2 GetPosition() { return _col->GetTransform()->GetPos(); }

	void Shoot(Vector2 startPos, Vector2 dir);
	void ShootEnd();

	void SetLeft()
	{
		for (auto sprite : _sprites)
			sprite->SetLeft();
	}
	void SetRight()
	{
		for (auto sprite : _sprites)
			sprite->SetRight();
	}

	bool _isActive = false;

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	State _curState = State::BALL;
	State _oldState = State::BALL;

	vector<shared_ptr<Sprite_Clip>> _sprites;
	vector <shared_ptr<Action>> _actions;
	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _trans;

	Vector2 _dir;

	float _speed = 100.0f;
	int _damage = 40;

	float _cooldownDuration = 1.0f; // 투사체 발사 쿨타임 지속 시간 (예: 1초)
	float _cooldownTimer = 0.0f;
	bool _canShoot = true;
};


