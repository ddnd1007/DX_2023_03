#pragma once
class MapleMonster
{
	enum State
	{
		STAND,
		WORK,
		HIT,
		DEAD,
	};
public:
	MapleMonster();
	~MapleMonster();

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
	void HitEnd();
	bool DeathAnimation();
	bool HitAnimation();
	void Move(shared_ptr<class PlayerManager> player);
	void ChangeState(State nextState, int duration);
	int getRandomNumber(int min, int max);


	shared_ptr<CircleCollider> GetCirCollider() { return _circleCol; }
	shared_ptr<RectCollider> GetRectCollider() { return _rectCol; }

	int _hp = 40;
	const int _maxHp = 40;
	bool _isDamaged = false;
	bool IsDead();
	bool IsActive() { return _hp > 0; }
	//shared_ptr<class MonsterHpBar> _hpBar;

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr<CircleCollider> _circleCol;
	shared_ptr<Transform> _circleTrans;
	shared_ptr<RectCollider> _rectCol;
	shared_ptr<Transform> _rectTrans;
	vector<shared_ptr<Action>> _actions;

	State _curState = State::WORK;
	State _oldState = State::WORK;

	bool _isAttack = false;
	bool _isDead = false;
	bool _isActive = true;
	bool _isInvincible;

	float _curTime = 0.0f;
	float _hitTime = 0.3f;
	const float _deathAnimationDuration = 0.9f;
	float _deathAnimationTimer = 0.0f;
	const float _hitAnimationDuration = 1.0f;
	float _hitAnimationTimer = 0.0f;
	const float _speed = 50.0f;
	const float _invincibleDuration = 1.0f;
	float _invincibleTimer;

	const int _damage = 3; 
	
};

