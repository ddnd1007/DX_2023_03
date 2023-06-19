#pragma once
class CupHead
{
	enum State
	{
		IDLE,
		RUN,
		ATTACK,
	};

public:
	CupHead();
	~CupHead();

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

	void Input();
	void Attack();

	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	void SetAction(State state);
	shared_ptr<Collider> GetCollider() { return _col; }

private:
	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	
	State _state = State::IDLE;

	bool _isFalling = false;
	bool _isAttack =false;

	float _speed = 300.0f;

	shared_ptr<class CupHeadBullet> bullet;
};

