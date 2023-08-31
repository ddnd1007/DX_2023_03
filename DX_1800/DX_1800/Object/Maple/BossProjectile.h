#pragma once
class Projectile
{
	enum State
	{
		BALL
	};
public:
	Projectile();
	~Projectile();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetDirection(Vector2 dir) { _dir = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }

	void SetAction(State state);

	void Attack(shared_ptr<class PlayerManager> victim);
	shared_ptr<CircleCollider> GetCollider() { return _col; }
	Vector2 GetPosition() { return _col->GetTransform()->GetPos(); }

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

	bool _isActive = false;

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	State _curState = State::BALL;
	State _oldState = State::BALL;

	vector<shared_ptr<Sprite_Clip>> _sprites;
	vector <shared_ptr<Action>> _actions;
	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _trans;

	Vector2 _dir;

	float _speed = 100.0f;
	int _damage = 40;
	
};


