#pragma once
class ArkanoidBrick
{
public:

	enum class ArkanoidBrickType
	{
		BRICK,
		NONE
	};

	ArkanoidBrick();
	~ArkanoidBrick();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _rect->SetCenter(pos); }
	void SetType(ArkanoidBrickType type) { _type = type; }
	ArkanoidBrickType GetType() { return _type; }
	bool IsDead() { return _isDead; }
	void SetDead(bool dead) { _isDead = dead; }
	shared_ptr<Collider> GetEachBlock() { return _rect; }

private:
	vector<HBRUSH> _brushes;
	bool _isDead = false;

	shared_ptr<Collider> _rect;
	ArkanoidBrickType _type = ArkanoidBrickType::NONE;
	
};

