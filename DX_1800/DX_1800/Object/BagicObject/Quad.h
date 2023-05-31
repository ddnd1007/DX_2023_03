#pragma once
class Quad
{
public:
	Quad(wstring path);

	void Update();
	void Render();

	void CreateVertices();
	void CreateData(wstring path);

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	vector<Vertex> _vertices;
	vector<UINT> _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<SRV> _srv;
	shared_ptr<SamplerState> _sampler;

	// 컴포넌트 패턴
	shared_ptr<Transform> _transform;
};

