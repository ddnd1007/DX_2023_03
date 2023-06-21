#pragma once
class CupBullet
{
public:
	CupBullet();
	~CupBullet();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetDirtection(Vector2 dir) { _direction = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }

	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	void Attack(shared_ptr<class CupMonster> victim);
	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive;
private:
	shared_ptr<Sprite_Clip> _sprite;
	shared_ptr<Action> _action;
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;

	Vector2 _direction;
	int _damage = 1;
	float _speed = 500.0f;
};

