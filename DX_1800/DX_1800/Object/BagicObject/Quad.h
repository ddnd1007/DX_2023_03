#pragma once
class Quad
{
protected:
	Quad() {}

public:
	Quad(wstring path);
	Quad(Vector2 size, wstring path);
	virtual ~Quad();

	virtual void Update();
	virtual void Render();

	virtual void CreateVertices();
	virtual void CreateData(wstring path);

protected:
	vector<Vertex_Texture> _vertices;
	vector<UINT> _indices;

	Vector2 _size;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<SRV> _srv;

};

