#pragma once
class MapleMap
{
public:
	MapleMap();
	~MapleMap();

	void Update();
	void Render();

	Vector2 leftBottom();
	Vector2 rightTop();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	shared_ptr<RectCollider> GetCollider() { return _col; }

private:
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _col2;
	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _transform2;
	shared_ptr<Quad>	_quad;
};

