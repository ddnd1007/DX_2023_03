#include "framework.h"
#include "Planet.h"

Planet::Planet(wstring name)
{
	wstring path = L"Resource/Texture/" + name + L".png";
	_quad = make_shared<Quad>(path);

	_orbit = make_shared<Transform>();
}

Planet::~Planet()
{
}

void Planet::Update()
{
	_quad->GetTransform()->AddAngle(_rotationSpeed);
	_orbit->AddAngle(_rotationSpeed * 1.5f);

	_quad->Update();
	_orbit->Update();
}

void Planet::Render()
{
	_quad->Render();
}

void Planet::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->SetPosition(pos);
	_orbit->SetPosition(pos);
}
