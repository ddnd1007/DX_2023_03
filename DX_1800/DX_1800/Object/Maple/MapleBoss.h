#pragma once
class MapleBoss
{
	enum State
	{
		STAND,
		WORK,
		BOSSHIT,
		SKILL,
		DEAD
	};
public:
	MapleBoss();
	~MapleBoss();

	void Update(Vector2 target);
	void Render();
	void PostRender();

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
	bool HitAnimation();
	void Attack(shared_ptr<class PlayerManager> victim);
	void HitEnd();
	bool DeathAnimation();
	void Move(shared_ptr<class PlayerManager> player);
	void Skill(Vector2 target);
	void SetStateWork() { State::WORK; }
	void DamagedEvent() { State::BOSSHIT; }

	shared_ptr<CircleCollider> GetCirCollider() { return _circleCol; }
	shared_ptr<RectCollider> GetRectCollider() { return _rectCol; }
	vector<shared_ptr<class Bossprojectiles>>& GetSkill() { return _skill1; }

	int _hp = 1000;
	const int _maxHp = 1000;
	bool _isDamaged = false;
	bool IsDead();
	bool IsActive() { return _hp > 0; }
	bool _move = true;
	bool _isSkill = false;

	//vector <shared_ptr<class BossSkill2>> _skill2;

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
	shared_ptr<HpBar> _hpBar;

	shared_ptr<PlayerManager> _player;

	vector<shared_ptr<class Bossprojectiles>> _skill1;


	State _curState = State::WORK;
	State _oldState = State::WORK;

	bool _isAttack = false;
	bool _isDead = false;
	bool _isActive = true;
	bool _skillUsed = false;
	
	float _curTime = 0.0f;
	float _hitTime = 0.3f;
	const float _deathAnimationDuration = 2.8f;
	float _deathAnimationTimer = 0.0f;

	const float _speed = 50.0f;
	
	const int _damage = 3;
	//const int _skill2Damage = 100;

	const float _hitAnimationDuration = 0.3f;
	float _hitAnimationTimer = 0.0f;

	float _CooldownDuration = 7.0f;
	float _CooldownTimer = 0.0f;
};

