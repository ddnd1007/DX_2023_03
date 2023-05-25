#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring path)
{
    CreateVertices();
    CreateData(path);
}

void Quad::Update()
{
}

void Quad::Render()
{
    _vertexBuffer->SetIA_VertexBuffer();
    _vs->SetIA_InputLayOut();
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    _srv->SetSRV(0);
    _sampler->SetSampler();

    _vs->Set_VS();
    _ps->Set_PS();

    DC->Draw(_vertices.size(), 0);
}

void Quad::CreateVertices()
{
    Vertex v;
    v.pos = { -0.5f, 0.5f, 0.0f }; // 왼쪽 위
    v.color = { 1.0f, 0.0f, 0.0f, 1.0f };
    v.uv = { 0.0f, 0.0f };
    _vertices.push_back(v);

    v.pos = { 0.5f, 0.5f, 0.0f }; // 오른쪽 위
    v.color = { 0.0f, 1.0f, 0.0f, 1.0f };
    v.uv = { 1.0f, 0.0f };
    _vertices.push_back(v);

    v.pos = { 0.5f, -0.5f, 0.0f }; // 오른쪽 아래
    v.color = { 0.0f, 0.0f, 1.0f, 1.0f };
    v.uv = { 1.0, 1.0f };
    _vertices.push_back(v);

    v.pos = { -0.5f, 0.5f, 0.0f }; // 왼쪽 위
    v.color = { 1.0f, 0.0f, 0.0f, 1.0f };
    v.uv = { 0.0f, 0.0f };
    _vertices.push_back(v);

    v.pos = { 0.5f, -0.5f, 0.0f }; // 오른쪽 아래
    v.color = { 0.0f, 0.0f, 1.0f, 1.0f };
    v.uv = { 1.0f, 1.0f };
    _vertices.push_back(v);

    v.pos = { -0.5f, -0.5f, 0.0f }; // 왼쪽 아래
    v.color = { 0.0f, 0.0f, 0.0f, 1.0f };
    v.uv = { 0.0f, 1.0f };
    _vertices.push_back(v);
}

void Quad::CreateData(wstring path)
{
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());
    _vs = make_shared<VertexShader>(L"Shader/TextureVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TexturePS.hlsl");

    _srv = make_shared<SRV>(path);
    _sampler = make_shared<SamplerState>();
}
