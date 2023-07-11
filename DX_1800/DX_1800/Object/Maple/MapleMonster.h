#pragma once
class MapleMonster
{
	enum State
	{
		STAND,
		WORK,
		ATTACK,
		DEAD,

	};
public:
	MapleMonster();
	~MapleMonster();

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

	void SetAction(State state);
	void Dead();

	shared_ptr<CircleCollider> GetCollider() { return _col; }


private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<CircleCollider> _col;

	State _curState = State::STAND;
	State _oldState = State::STAND;

	bool _isAttack = false;
	bool _isDead = false;

	int _hp = 3;
	int _damage;
};

