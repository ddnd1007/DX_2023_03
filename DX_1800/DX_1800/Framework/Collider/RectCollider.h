#pragma once
class RectCollider
{
public:
	RectCollider(Vector2 size);
	~RectCollider();

	void Update();
	void Render();

	void CreateVertices();
	void CreateData();

	shared_ptr<Transform> GetTransform() { return _transform; }


private:
	Vector2 _size;
	shared_ptr<ColorBuffer> _color;

	shared_ptr<Transform> _transform;

	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
};

