#pragma once
class MapleBoss
{

	enum State
	{
		STAND,
		WORK,
		HIT,
		DEAD
	};
public:
	MapleBoss();
	~MapleBoss();

	void Update();
	void Render();

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

	void SetPosition(Vector2 pos) { _circleCol->GetTransform()->SetPosition(pos); }
	void SetAction(State state);
	void TakeDamage(int damage);
	void Hit(shared_ptr<class PlayerManager> player);
	void Attack(shared_ptr<class PlayerManager> victim);
	void HitEnd();
	bool DeathAnimation();
	void Move(shared_ptr<class PlayerManager> player);
	void ChangeState(State nextState, int duration);
	void Skill();

	void SetBallCol(Vector2 pos) { return _ballCol->GetTransform()->SetPosition(pos); }

	shared_ptr<CircleCollider> GetCirCollider() { return _circleCol; }
	shared_ptr<RectCollider> GetRectCollider() { return _rectCol; }

	int _hp = 200;
	bool _isDamaged = false;
	bool IsDead();
	bool IsActive() { return _hp > 0; }

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr<CircleCollider> _circleCol;
	shared_ptr<Transform> _circleTrans;
	shared_ptr<CircleCollider> _ballCol;
	shared_ptr<Transform> _ballTrans;
	shared_ptr<RectCollider> _rectCol;
	shared_ptr<Transform> _rectTrans;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<class BossProjectile> _skill;
	shared_ptr<HpBar> _hpBar;

	State _curState = State::WORK;
	State _oldState = State::WORK;

	bool _isAttack = false;
	bool _isDead = false;
	bool _isActive = true;
	
	float _curTime = 0.0f;
	float _hitTime = 0.3f;
	const float _deathAnimationDuration = 0.2f;
	float _deathAnimationTimer = 0.0f;
	const float _speed = 50.0f;
	
	const int _damage = 3;
};

