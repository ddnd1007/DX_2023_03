#pragma once
class CupMonster
{
public:
	enum State
	{
		IDLE,
		LOOP,
		DIE,
		END
	};
	CupMonster();
	~CupMonster();

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
	void TakeDamage(int damage);
	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetAction(State state);
	void PostRender();

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

	bool IsDead() { return _hp <= 0; }
	bool IsDamaged() { return _isDamaged; }
	bool IsActive() { return _hp > 0; }


private:
	void CreateAction(string name, float speed, Action::Type type, CallBack callBack);

	shared_ptr<RectCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr<FilterBuffer> _filterBuffer;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	int _hp = 20;
	bool _isDamaged = false;
	bool _isActive = true;

	float _curTime = 0.0f;
	float _damageTime = 0.2f;
};

