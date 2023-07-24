#pragma once
class MaplePlayer
{
	enum State
	{
		STAND,
		WORK,
		JUMP,
		SHOOT,
		DEAD,
		LAYDOWN
	};
public:
	MaplePlayer();
	~MaplePlayer();

	void Update();
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
	void SetAction(State state);
	void Input();
	void Jump();
	void Attack();
	void EndAttack();
	void Dead();
	void LayDown();
	void TakeDamage(int _hp);

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	vector<shared_ptr<class MapleArrow>>& GetBullets() { return _arrows; }

	bool IsFalling() { return _isFalling; }
	bool _isDamaged = false;

	void SetIsFalling(bool value) { _isFalling = value; }
	void Grounded() { _isFalling = false; }

	int _hp = 100;

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	shared_ptr<CircleCollider> _col;
	shared_ptr<CircleCollider> _bowCol;
	
	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _bowTrans;

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	vector<shared_ptr<class MapleArrow>> _arrows;

	State _curState = State::STAND;
	State _oldState = State::STAND;

	bool _isFalling;
	bool _isAttack = false;

	bool _isDead = false;

	float _jumpPower = 0.0f;
	float _maxFalling = 800.0f;
	float _speed = 200.0f;


};

