#pragma once
class Bossprojectiles
{
	enum State
	{
		BALL
	};
public:
	Bossprojectiles();
	~Bossprojectiles();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetDirection(Vector2 dir) { _dir = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }

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

	const shared_ptr<CircleCollider>& GetSkillCollider() { return _col; }
	void Shoot(Vector2 startPos, Vector2 dir);
	void SetAction(State state);
	void EndEvent();
	void SetAngle(float value) { _col->GetTransform()->SetAngle(value); }
	void SetDirtection(Vector2 dir) { _dir = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }
	
	shared_ptr<CircleCollider> GetCollider() { return _col; }
	Vector2 GetPosition() { return _col->GetTransform()->GetPos(); }

	bool IsActive() { return _isActive; }
	

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);
	vector<shared_ptr<Sprite_Clip>> _sprites;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Transform> _trans;

	shared_ptr<CircleCollider> _col;

	State _curState = State::BALL;
	State _oldState = State::BALL;

	Vector2 _dir = Vector2(0.0f, 0.0f);

	bool _isActive = true;
	bool _isAttack = false;;
	float _speed = 200.0f;
	int _damage = 40;

	float _cooldownDuration = 4.0f; // 투사체 발사 쿨타임 지속 시간 (예: 1초)
	float _cooldownTimer = 0.0f;

};


