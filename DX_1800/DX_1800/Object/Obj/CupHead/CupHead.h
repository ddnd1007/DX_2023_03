#pragma once
class CupHead
{
	enum State
	{
		IDLE,
		RUN,
		ATTACK
	};
public:
	CupHead();
	~CupHead();

	void Update();
	void Render();
	void PostRender();

	void SetLeft()
	{
		for (auto sprite : _sprite)
			sprite->SetLeft();
	}

	void SetRight()
	{
		for (auto sprite : _sprite)
			sprite->SetRight();
	}

	void Input();

	void CreateAction(string name, float speed = 0.1f, Action::Type type, CallBack callback = nullptr);

	void SetAction(State state);


private:
	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprite;

	State _state = State::IDLE;

	bool isAttack = false;

	float _speed = 300.0f;
};

