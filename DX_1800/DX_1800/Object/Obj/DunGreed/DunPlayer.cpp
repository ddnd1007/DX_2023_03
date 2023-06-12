#include "framework.h"
#include "DunPlayer.h"
#include "DunBullet.h"

DunPlayer::DunPlayer()
{
	_player = make_shared<Quad>(L"Resource/Texture/Player.png");
	_bowTrans = make_shared<Transform>();

	_bow = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_bulletTrans = make_shared<Transform>();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<DunBullet> bullet = make_shared<DunBullet>();
		_bullets.push_back(bullet);
	}

	_bowTrans->SetParent(_player->GetTransform());

	_bow->GetTransform()->SetAngle(-PI * 0.75f);
	_bow->GetTransform()->SetPosition(Vector2(80.0f, 0.0f));
	_bow->GetTransform()->SetParent(_bowTrans);

	_bulletTrans->SetParent(_bow->GetTransform());
	_bulletTrans->SetPosition(Vector2(-20.0f, 20.0f));
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::Update()
{
	_bowTrans->SetAngle((MOUSE_POS - _bowTrans->GetWorldPos()).Angle());

	for (auto bullet : _bullets)
	{
		if (bullet->IsActive() == false)
			bullet->GetColliderTransform()->SetPosition(_bulletTrans->GetWorldPos());
	}

	Move();
	Fire();

	_player->Update();
	_bowTrans->Update();
	_bow->Update();
	_bulletTrans->Update();

	for (auto bullet : _bullets)
		bullet->Update();
}

void DunPlayer::Render()
{
	for (auto bullet : _bullets)
		bullet->Render();
	_bow->Render();
	_player->Render();
}

void DunPlayer::Move()
{
	if (KEY_PRESS('A'))
	{
		_pos.x -= _speed * DELTA_TIME;
	}
	if (KEY_PRESS('D'))
	{
		_pos.x += _speed * DELTA_TIME;
	}
	if (KEY_PRESS('W'))
	{
		_pos.y += _speed * DELTA_TIME;
	}
	if (KEY_PRESS('S'))
	{
		_pos.y -= _speed * DELTA_TIME;
	}

	_player->GetTransform()->SetPosition(_pos);
}

void DunPlayer::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		shared_ptr<DunBullet> bullet = SetBullet();

		if (bullet == nullptr)
			return;

		bullet->SetPos(_bulletTrans->GetWorldPos());
		bullet->SetDir((MOUSE_POS - _bowTrans->GetWorldPos()));
		bullet->SetActive(true);
	}
}

shared_ptr<DunBullet> DunPlayer::SetBullet()
{
	for (auto bullet : _bullets)
	{
		if (bullet->IsActive() == true)
			continue;
		else
			return bullet;
	}
	return nullptr;
}
