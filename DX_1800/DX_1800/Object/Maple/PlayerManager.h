#pragma once
class PlayerManager
{
public:

	enum State
	{
		STAND,
		WORK,
		JUMP,
		SHOOT,
		DEAD,
	};

	PlayerManager();
	~PlayerManager();


	static void Create()
	{
		if (_instance == nullptr)
			_instance = new PlayerManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static PlayerManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}


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
	int& GetHp() { return _hp; }

	void SetAction(State state);
	void Input();
	void Jump();
	void Attack();
	void EndAttack();
	void TakeDamage(int damage);
	Vector2 GetPosition() { return _col->GetTransform()->GetPos(); }

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	vector<shared_ptr<class MapleArrow>>& GetBullets() { return _arrows; }

	bool IsFalling() { return _isFalling; }
	bool IsActive() { return _hp > 0; }
	bool IsDead();
	bool _isDamaged = false;


	void SetIsFalling(bool value) { _isFalling = value; }
	void Grounded() { _isFalling = false; }

private:
	static PlayerManager* _instance;

	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	shared_ptr<CircleCollider> _col;
	shared_ptr<CircleCollider> _bowCol;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _bowTrans;

	shared_ptr<class MapleInventory> _inven;

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	vector<shared_ptr<class MapleArrow>> _arrows;

	shared_ptr<class PlayerHpBar> _hpBar;

	State _curState = State::STAND;
	State _oldState = State::STAND;

	bool _isFalling;
	bool _isAttack = false;
	bool _isWork = false;
	bool _isDead = false;
	bool _isInvincible;

	float _invincibleTimer;
	const float _invincibleDuration = 1.0f;
	float _jumpPower = 0.0f;
	float _knockBack = 0.0f;
	float _maxFalling = 800.0f;
	float _speed = 200.0f;

	int _hp = 100;
	int _maxHp = 100;
	
};

