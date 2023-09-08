#pragma once
class BossSkill2
{
	enum State
	{
		SKILL,
	};



public:
	BossSkill2();
	~BossSkill2();

	void Update();
	void Render();

	void EndSkill();

	void SetPosition(Vector2 pos) { _cirCol->GetTransform()->SetPosition(pos); }
	void SetDirection(Vector2 dir) { _dir = dir.NorMalVector2(); _cirCol->GetTransform()->SetAngle(dir.Angle()); }

	void SetAction(State state);

	void Skill2(shared_ptr<class PlayerManager> victim);

	int getRandomNumber(int min, int max);
	shared_ptr<CircleCollider> GetCirCollider() { return _cirCol; }
	shared_ptr<RectCollider> GetRectCollider() { return _rectCol; }
	Vector2 GetPosition() { return _cirCol->GetTransform()->GetPos(); }

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

	bool _isActive = true;
	bool _skillActive = false;

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	State _curState = State::SKILL;
	State _oldState = State::SKILL;

	vector<shared_ptr<Sprite_Clip>> _sprites;
	vector <shared_ptr<Action>> _actions;
	shared_ptr<CircleCollider> _cirCol;
	shared_ptr<RectCollider> _rectCol;
	shared_ptr<Transform> _cirTrans;
	shared_ptr<Transform> _rectTrans;

	Vector2 _dir;

	float _speed = 100.0f;
	int _damage = 100;

};


