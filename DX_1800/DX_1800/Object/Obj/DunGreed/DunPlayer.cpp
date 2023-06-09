#include "framework.h"
#include "DunPlayer.h"

#include "DunBullet.h"

DunPlayer::DunPlayer()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Player.png");
	_bowAngle = make_shared<Transform>();
	_bow = make_shared<Quad>(L"Resource/Texture/bow.png");
	_muzzle = make_shared<Transform>();
	_bullet = make_shared<DunBullet>();
	for (int i = 0; i < 30; i++)
	{
		shared_ptr<DunBullet> bullet = make_shared<DunBullet>();
		_bullets.push_back(bullet);
	}
	_quad->GetTransform()->SetPosition(Vector2(80.0f, 50.0f));
	_bowAngle->SetParent(_quad->GetTransform());

	_bow->GetTransform()->SetParent(_bowAngle);
	_bow->GetTransform()->SetPosition(Vector2{ 70.0f, 0.0f });
	_bow->GetTransform()->SetAngle(-PI * 0.75f);

	_muzzle->SetParent(_bowAngle);
	_muzzle->SetPosition(Vector2(120.0f, 0.0f));
}
DunPlayer::~DunPlayer()
{
}
void DunPlayer::Update()
{
	_bowAngle->SetAngle((MOUSE_POS - _bowAngle->GetWorldPos() + Vector2(0.0f, -36.0f)).Angle());

	Fire();

	Move();
	_quad->Update();
	_bowAngle->Update();
	_bow->Update();
	_muzzle->Update();
	_bullet->Update();
	
	for (auto bullet : _bullets)
		bullet->Update();

}
void DunPlayer::Render()
{
	_bullet->Render();
	for (auto bullet : _bullets)
	bullet->Render();
	_bow->Render();
	_quad->Render();;

}
void DunPlayer::Fire()
{
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		_mousePress = true;
		_mouseUp = false;
	}
	else
	{
		_mouseUp = true;
	}
	if (_mousePress == true && _mouseUp == true)
	{
		shared_ptr<DunBullet> bullet = SetBullet();

		if (bullet == nullptr)
			return;

		bullet->SetPos(_muzzle->GetWorldPos());
		bullet->SetDir((MOUSE_POS - _bowAngle->GetWorldPos() + Vector2(0.0f, -35.0f)));
		bullet->SetActive(true);

		_mousePress = false;
		_mouseUp = false;
	}
}
shared_ptr<DunBullet> DunPlayer::SetBullet()
{
	for (auto bullet : _bullets)
	{
		if (bullet->IsActive() == false)
			return bullet;
	}
	return nullptr;
}

void DunPlayer::Move()
{
	
	if (_pos.x > WIN_WIDTH)
	{
		_pos.x = WIN_WIDTH;
	}
	else if (_pos.x < 0.0f)
	{
		_pos.x = 0.0f;
	}
	else if (_pos.y > WIN_HEIGHT)
	{			
		_pos.y = WIN_HEIGHT;
	}
	else if (_pos.y < 0.0f)
	{
		_pos.y = 0.0f;
	}
	else
	{
		if (KEY_PRESS('A'))
		{
			_pos.x -= _speed;
		}
		if (KEY_PRESS('D'))
		{
			_pos.x += _speed;
		}
		if (KEY_PRESS('W'))
		{
			_pos.y += _speed;
		}
		if (KEY_PRESS('S'))
		{
			_pos.y -= _speed;
		}
	}

	_quad->GetTransform()->SetPosition(_pos);
	
}


