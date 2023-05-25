#pragma once
class Quad
{
public:
	Quad();
	Quad(wstring path);

	void Update();
	void Render();

	void CreateVertices();
	void CreateData(wstring path);

private:
	vector<Vertex> _vertices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<SRV> _srv;
	shared_ptr<SamplerState> _sampler;
};

