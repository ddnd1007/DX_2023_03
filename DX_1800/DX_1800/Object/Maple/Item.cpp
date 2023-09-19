#include "framework.h"
#include "Item.h"

Item::Item()
{
	_quad = make_shared<Quad>(L"", Vector2(36.0f, 35.0f));
	_trans = make_shared<Transform>();
	_col = make_shared<RectCollider>(Vector2(36.0f, 35.0f));

	_trans->SetParent(_col->GetTransform());
}

Item::Item(wstring path, ItemInfo info)
	:info(info)
{
	_quad = make_shared<Quad>(path, Vector2(36.0f, 35.0f));
	_trans = make_shared<Transform>();
	_col = make_shared<RectCollider>(Vector2(36.0f, 35.0f));

	_trans->SetParent(_col->GetTransform());
}

Item::~Item()
{
}

void Item::Update()
{
	_quad->Update();
	_col->Update();
	_trans->Update();
}

void Item::Render()
{
	_trans->SetWorldBuffer(0);
	_quad->Render();
	_col->Render();
}

void Item::SetQuad(wstring path)
{
	_quad = make_shared<Quad>(path, Vector2(36.0f, 35.0f));
}

bool Item::colision(Vector2 mouse, shared_ptr<RectCollider> rect)
{
	if (_col->IsCollision(mouse))
	{
		drag = true;
	}

	if (_col->IsCollision(mouse) && _col->IsCollision(rect))
	{
		drag = false;
	}

	return drag;
}
