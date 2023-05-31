#include "framework.h"
#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	// 과제1
	// Planet이라는 클래스 구현
	// 태양, 지구, 달

	// _sun = make_shared<Planet>(L"Resource/Texture/sun.png")

	_sun = make_shared<Quad>(L"Resource/Texture/sun.png");
	_earth = make_shared<Quad>(L"Resource/Texture/earth.png");
	_moon = make_shared<Quad>(L"Resource/Texture/moon.png");
	_earthRotating = make_shared<Transform>();
	_moonRotating = make_shared<Transform>();

	_sun->GetTransform()->SetPosition(CENTER);

	_sun->GetTransform()->SetScale(Vector2(0.3f, 0.3f));
	_earth->GetTransform()->SetScale(Vector2(0.3f, 0.3f));
	_moon->GetTransform()->SetScale(Vector2(0.3f, 0.3f));

	_earth->GetTransform()->SetParent(_sun->GetTransform());
	_earthRotating->SetParent(_sun->GetTransform());
	_earth->GetTransform()->SetPosition(Vector2(800.0f, 0.0f));

	_moon->GetTransform()->SetParent(_earth->GetTransform());
	_moonRotating->SetParent(_sun->GetTransform());
	_moon->GetTransform()->SetPosition(Vector2(1000.0f, 0.0f));
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::Update()
{
	_sun->GetTransform()->AddAngle(0.0001f);

	_earth->GetTransform()->AddAngle(0.0003f);
	_earthRotating->AddAngle(-0.0005f);

	_moon->GetTransform()->AddAngle(0.0001f);
	_moonRotating->AddAngle(-0.0006f);

	_sun->Update();
	_earth->Update();
	_earthRotating->Update();
	_moon->Update();
	_moonRotating->Update();
	
}

void SolarSystem::Render()
{
	_sun->Render();
	_earth->Render();
	_moon->Render();
}
