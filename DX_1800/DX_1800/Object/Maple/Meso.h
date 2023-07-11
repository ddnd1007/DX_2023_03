#pragma once
class Meso
{
	enum State
	{
		MESO1,
	};
public:
	Meso();
	~Meso();

	void Update();
	void Render();

	void SetAction(State state);
	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	shared_ptr<CircleCollider> _col;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	shared_ptr<Transform> _trans;
	vector<shared_ptr<Action>> _actions;

	State _curState = State::MESO1;
	State _oldState = State::MESO1;

};

