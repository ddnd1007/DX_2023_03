#pragma once
class CupBullet
{
public:
	enum State
	{
		INTRO,
		LOOP
	};

	CupBullet();
	~CupBullet();

	void Update();
	void Render();

	void Fire(Vector2 startPos, Vector2 dir);
	void EndEvent();

	shared_ptr<CircleCollider> GetCollider() { return _col; }

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

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);
	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::INTRO;
	State _oldState = State::INTRO;

	Vector2 _dir;
	bool _isActive;
	float _speed = 500.0f;
};


