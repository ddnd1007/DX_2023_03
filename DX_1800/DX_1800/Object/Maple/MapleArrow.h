#pragma once
class MapleArrow
{
public:
	MapleArrow();
    ~MapleArrow();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetDirtection(Vector2 dir) { _dir = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }


	void Attack(shared_ptr<class MapleMonster> victim);
	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive;

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);
	shared_ptr<CircleCollider> _col;
	shared_ptr<Sprite_Clip> _sprite;
	shared_ptr<Transform> _trans;
	shared_ptr<Action> _action;


	Vector2 _dir;

	float _speed = 400.0f;
	int _damage = 1;
};

