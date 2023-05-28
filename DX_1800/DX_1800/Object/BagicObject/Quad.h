#pragma once
class Quad
{
public:
	Quad(wstring path);

	void Update();
	void Render();

	void CreateVertices();
	void CreateData(wstring path);

private:
	vector<Vertex> _vertices;
	vector<UINT> _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<SRV> _srv;
	shared_ptr<SamplerState> _sampler;
};

