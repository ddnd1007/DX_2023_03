#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	:_size(size)
{
	CreateVertices();
	CreateData();

    _type = Type::RECT;
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _colorBuffer->Update_Resource();
    _colorBuffer->SetColor(_color);
    _transform->Update();
}

void RectCollider::Render()
{
    _transform->SetWorldBuffer(0);
    _colorBuffer->SetPS_Buffer(0);

    _vertexBuffer->SetIA_VertexBuffer();
    _vs->SetIA_InputLayOut();

 
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); // ������ ����� �۾�

    _vs->Set_VS();
    _ps->Set_PS();

    DC->Draw(_vertices.size(),0);

}

void RectCollider::CreateVertices()
{
    Vertex v;

    Vector2 halfSize = _size * 0.5f; // ������ ����� �۾��� �簢���̸� ������ 5�� �ʿ���

    v.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
    _vertices.push_back(v);

    v.pos = { halfSize.x, halfSize.y, 0.0f }; // ������ ��
    _vertices.push_back(v);

    v.pos = { halfSize.x, -halfSize.y, 0.0f }; // ������ �Ʒ�
    _vertices.push_back(v);

    v.pos = { -halfSize.x, -halfSize.y, 0.0f }; // ���� �Ʒ�
    _vertices.push_back(v);

    v.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
    _vertices.push_back(v);
}

void RectCollider::CreateData()
{
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());
    _colorBuffer = make_shared<ColorBuffer>();

    _vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    AABB_info info = GetAABB_Info();

    Vector2 circleWorldPos = other->GetWorldPos();

    float circleLeft =      GetWorldPos().x - other->GetWorldRadius();
    float circleRight =     GetWorldPos().x + other->GetWorldRadius();
    float circleTop =       GetWorldPos().y + other->GetWorldRadius();
    float circleBottom =    GetWorldPos().y - other->GetWorldRadius();

    if (other->GetWorldPos().x < info.right && other->GetWorldPos().x > info.left)
    {
        if (circleBottom < info.bottom && circleTop > info.bottom)
        {
            return true;
        }
    }

    if (other->GetWorldPos().y > Bottom() && other->GetWorldPos().y < Top())
    {
        if (other->Left() < Right() && other->Right() > Left())
        {
            return true;
        }
    }

    if (other->IsCollision(Vector2(Left(), Top()))
        || other->IsCollision(Vector2(Right(), Top()))
        || other->IsCollision(Vector2(Left(), Bottom()))
        || other->IsCollision(Vector2(Right(), Bottom())))
    {
        return true;
    }

    return false;
}

RectCollider::AABB_info RectCollider::GetAABB_Info()
{
    AABB_info info;
    info.left =     _transform->GetWorldPos().x - _size.x * _transform->GetWorldScale().x;
    info.right =    _transform->GetWorldPos().x + _size.x * _transform->GetWorldScale().x;
    info.top =      _transform->GetWorldPos().y + _size.x * _transform->GetWorldScale().y;
    info.bottom =   _transform->GetWorldPos().y - _size.x * _transform->GetWorldScale().y;
    return info;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    AABB_info aInfo = GetAABB_Info();
    AABB_info bInfo = other->GetAABB_Info();

    if (aInfo.left > bInfo.right || aInfo.right < bInfo.left
        || aInfo.top < bInfo.bottom || aInfo.bottom > bInfo.top)
        return false;

    return true;
}


bool RectCollider::IsCollision(const Vector2& pos)
{
    AABB_info info;
    if (pos.x > info.left && pos.x < info.right)
    {
        if (pos.y > info.bottom && pos.y < info.top)
            return true;
    }
    return false;
}



