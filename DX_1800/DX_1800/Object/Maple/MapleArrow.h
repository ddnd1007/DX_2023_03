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
	Vector2 GetPosition() { return _col->GetTransform()->GetPos(); }


	bool _isActive;

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _trans;

	Vector2 _dir;

	float _speed = 400.0f;
	int _damage = 1;
};

