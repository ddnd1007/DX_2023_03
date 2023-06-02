#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	:_size(size)
{
	CreateVertices();
	CreateData();

    _transform = make_shared<Transform>();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _transform->Update();
}

void RectCollider::Render()
{
    _transform->SetWorldBuffer(0);

    _vertexBuffer->SetIA_VertexBuffer();

 
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); // 선으로 만드는 작업

    _vs->Set_VS();
    _ps->Set_PS();

    DC->Draw(_vertices.size(),0);

}

void RectCollider::CreateVertices()
{
    Vertex v;

    Vector2 halfSize = _size * 0.5f; // 선으로 만드는 작업은 사각형이면 정점이 5개 필요함

    v.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    _vertices.push_back(v);

    v.pos = { halfSize.x, halfSize.y, 0.0f }; // 오른쪽 위
    _vertices.push_back(v);

    v.pos = { halfSize.x, -halfSize.y, 0.0f }; // 오른쪽 아래
    _vertices.push_back(v);

    v.pos = { -halfSize.x, -halfSize.y, 0.0f }; // 왼쪽 아래
    _vertices.push_back(v);

    v.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    _vertices.push_back(v);
}

void RectCollider::CreateData()
{
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

    _vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

    _color = make_shared<ColorBuffer>();

    
}
