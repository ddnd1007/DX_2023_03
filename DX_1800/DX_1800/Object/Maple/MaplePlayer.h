#pragma once
class MaplePlayer
{
	enum State
	{
		STAND,
		WORK,
		JUMP,
		DIE
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

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool IsFalling() { return _isFalling; }
	void SetIsFalling(bool value) { _isFalling = value; }
	void Grounded() { _isFalling = false; }

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::STAND;
	State _oldState = State::STAND;

	bool _isFalling;
	bool _isAttack = false;

	float _jumpPower = 0.0f;
	float _maxFalling = 800.0f;

	float _speed = 200.0f;
};

