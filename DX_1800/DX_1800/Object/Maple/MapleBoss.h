#pragma once
class MapleBoss
{
	enum State
	{
		STAND,
		STAND2,
		ATTACK2,
		DIE
	};

public:
	MapleBoss();
	~MapleBoss();

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

	void TakeDamage(int damage);
	void SetAction(State state);
	void PostRender();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	shared_ptr<CircleCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

	int& GetHp() { return _hp; }
	bool IsDead() { return _hp <= 0; }
	bool IsDamaged() { return _isDamaged; }
	bool IsActive() { return _hp > 0; }


private:
	void CreateAction(string name, float speed, Action::Type type, CallBack callBack);

	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr<FilterBuffer> _filterBuffer;

	State _curState = State::STAND;
	State _oldState = State::STAND;

	int _hp = 20;
	bool _isDamaged = false;
	bool _isActive = true;

	float _curTime = 0.0f;
	float _damageTime = 0.2f;
};


