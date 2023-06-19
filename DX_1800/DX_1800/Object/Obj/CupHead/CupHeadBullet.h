#pragma once
class CupHeadBullet
{
public:
	enum State
	{
		INTRO,
		LOOP
	};
	CupHeadBullet();
	~CupHeadBullet();

	void Update();
	void Render();

	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	void Fire(Vector2 startPos, Vector2 dir);
	void EndEvent();

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
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr < Transform> _spriteTrans;
	shared_ptr<CircleCollider> _col;

	State _state = State::INTRO;

	Vector2 _dir;

	float _speed = 550.0f;
	bool _isActive = false;

};

