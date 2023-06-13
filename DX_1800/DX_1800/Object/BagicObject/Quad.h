#pragma once
class Quad
{
public:
	Quad(wstring path);
	Quad(Vector2 size, wstring path);
	~Quad();

	void Update();
	void Render();

	void CreateVertices();
	void CreateData(wstring path);

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	vector<Vertex_Texture> _vertices;
	vector<UINT> _indices;

	Vector2 _size;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<SRV> _srv;

	// 컴포넌트 패턴
	shared_ptr<Transform> _transform;
};

