#include "framework.h"
#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	_sun = make_shared<Planet>(L"sun");
	_sun->SetScale({0.3f, 0.3f});
	_sun->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));

	_earth = make_shared<Planet>(L"earth");
	_earth->SetScale({0.3f, 0.3f});
	_earth->SetRotation(0.0002f);

	_moon = make_shared<Planet>(L"moon");
	_moon->SetScale({0.3f,0.3f});
	_moon->SetRotation(0.0003f);

	_earth->SetPosition(Vector2(800.0f,0.0f));
	_moon->SetPosition(Vector2(800.0f, 0.0f));

	_sun->SetPosition(CENTER);

	_earth->SetParent(_sun->GetOrbit());
	_moon->SetParent(_earth->GetOrbit());

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.selected = 6;
	_filterBuffer->_data.imageSize = _sun->GetImageSize();
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::Update()
{
	if(KEY_PRESS('A'))
		_sun->SetPosition(WIN_MOUSE_POS);

	if (KEY_PRESS('D'))
	{
		Vector2 start = _sun->GetTransform()->GetWorldPos();
		Vector2 end = WIN_MOUSE_POS;

		_sun->SetPosition(LERP(start,end, 0.001f));
	}
		

	_sun->Update();
	_earth->Update();
	_moon->Update();
	
	_filterBuffer->Update_Resource();
}

void SolarSystem::Render()
{
	_earth->Render();
	_filterBuffer->SetPS_Buffer(0);
	_sun->Render();
	_moon->Render();
}
