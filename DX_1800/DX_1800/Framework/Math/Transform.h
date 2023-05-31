#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void Update_SRT();
	void Update_WorldBuffer();

	void SetWorldBuffer(UINT slot);
	void SetPosition(Vector2 pos) { _pos = pos; }
	void SetScale(Vector2 scale) { _scale = scale; }
	void SetAngle(float angle) { _angle = angle; }

	void AddVector2(Vector2 pos) { _pos += pos; }
	void AddScale(Vector2 scale) { _scale += scale; }
	void AddAngle(float angle) { _angle += angle; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	const XMMATRIX& GetSRT() { return _srtMatrix; }

	Vector2 GetScale() { return _scale; }

private:
	Vector2 _pos;
	Vector2 _scale = { 1.0f, 1.0f };

	float _angle = 0.0f;

	XMMATRIX _srtMatrix = XMMatrixIdentity();

	shared_ptr<class MatrixBuffer> _world;
	weak_ptr<Transform> _parent;
};

