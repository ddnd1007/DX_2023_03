#include "framework.h"
#include "DunPlayer.h"
#include "DunBullet.h"

DunPlayer::DunPlayer()
{
	_col = make_shared<CircleCollider>(0.0f);
	_quadTrans = make_shared<Transform>();
	_player = make_shared<Quad>(L"Resource/Texture/Player.png");
	_bowTrans = make_shared<Transform>();
	_bow = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_bulletTrans = make_shared<Transform>();

	_bibleTrans = make_shared<Transform>();

	for (int i = 0; i < 10; i++)
	{
		shared_ptr<DunBullet> bullet = make_shared<DunBullet>();
		_bullets.push_back(bullet);
	}

	_quadTrans->SetParent(_col->GetTransform());

	_bowTrans->SetParent(_quadTrans->GetTransform());

	_bow->GetTransform()->SetAngle(-PI * 0.75f);
	_bow->GetTransform()->SetPosition(Vector2(80.0f, 0.0f));
	_bow->GetTransform()->SetParent(_bowTrans);

	_bulletTrans->SetParent(_bow);
	_bulletTrans->SetPosition(Vector2(-20.0f, 20.0f));

	_bibleTrans->SetPosition(_col->GetWorldPos());

	for (int i = 0; i < 3; i++)
	{
		shared_ptr<CircleCollider> bible = make_shared<CircleCollider>(15.0f);
		float xPos = cos(2 * PI / 3 * i) * 120.0f;
		float yPos = sin(2 * PI / 3 * i) * 120.0f;
		bible->GetTransform()->SetPosition(Vector2(xPos, yPos));
		bible->GetTransform()->SetParent(_bibleTrans);
		_bibles.push_back(bible);
	}
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
			bullet->GetTransform()->SetPosition(_bulletTrans->GetWorldPos());
	}

	_bibleTrans->SetPosition(_col->GetWorldPos());
	_bibleTrans->AddAngle(3.0f * DELTA_TIME);

	Move();
	Fire();

	_player->Update();
	_quadTrans->Update();
	_col->Update();
	_bowTrans->Update();
	_bow->Update();
	_bulletTrans->Update();

	_bibleTrans->Update();

	for (auto bullet : _bullets)
		bullet->Update();

	for (auto bible : _bibles)
		bible->Update();

	for (auto bibleQuad : _bibleQuads)
		bibleQuad->Update();
}

void DunPlayer::Render()
{
	for (auto bullet : _bullets)
		bullet->Render();

	for (auto bibleQuad : _bibleQuads)
		bibleQuad->Render();

	for (auto bible : _bibles)
		bible->Render();

	_bow->Render();
	_player->Render();
	_col->Render();
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

	_col->GetTransform()->SetPosition(_pos);
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
