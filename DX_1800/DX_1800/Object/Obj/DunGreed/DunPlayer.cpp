#include "framework.h"
#include "DunPlayer.h"
#include "DunBullet.h"
#include "DunMonster.h"

DunPlayer::DunPlayer()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Player.png");
	_bowSlot = make_shared<Transform>();
	_trans = make_shared<Transform>();
	_trans->SetParent(_quad->GetTransform());
	_bowQuad = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_bowQuad->GetTransform()->SetParent(_bowSlot);

	_bible1 = make_shared<CircleCollider>(500.0f);
	_bible1->GetTransform()->SetParent(_trans);
	_bible1->GetTransform()->SetScale(Vector2(0.05f, 0.05f));
	_bible1->GetTransform()->SetPosition(Vector2(70.0f, 70.0f));


	_bible2 = make_shared<CircleCollider>(500.0f);
	_bible2->GetTransform()->SetParent(_trans);
	_bible2->GetTransform()->SetScale(Vector2(0.05f, 0.05f));
	_bible2->GetTransform()->SetPosition(Vector2(-70.0f, 70.0f));


	_bible3 = make_shared<CircleCollider>(500.0f);
	_bible3->GetTransform()->SetParent(_trans);
	_bible3->GetTransform()->SetScale(Vector2(0.05f, 0.05f));
	_bible3->GetTransform()->SetPosition(Vector2(-35.0f, -70.0f));



	_bowQuad->GetTransform()->SetPosition(Vector2(100.0f, 0.0f));
	_bowQuad->GetTransform()->SetAngle(-PI * 0.75f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<DunBullet> bullet = make_shared<DunBullet>();
		_bullets.push_back(bullet);
	}
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::Update()
{

	Vector2 slotToMousePos = MOUSE_POS - _bowSlot->GetPos();
	float angle = slotToMousePos.Angle();

	Move();
	InPut();

	_quad->Update();
	_bowSlot->SetPosition(_quad->GetTransform()->GetPos());
	_bowSlot->Update();

	_trans->AddAngle(_rotationSpeed * 15.0f);

	_trans->Update();
	_bible1->Update();
	_bible2->Update();
	_bible3->Update();

	_bowQuad->Update();
	_bowSlot->SetAngle(angle);

	for (auto bullet : _bullets)
		bullet->Update();
}

void DunPlayer::Render()
{
	_quad->Render();
	_bowQuad->Render();

	_bible1->Render();
	_bible2->Render();
	_bible3->Render();

	for (auto bullet : _bullets)
		bullet->Render();
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

	_quad->GetTransform()->SetPosition(CENTER);
}

void DunPlayer::InPut()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 start = _bowQuad->GetTransform()->GetWorldPos();
		Vector2 direction = (MOUSE_POS - start).NorMalVector2();

		auto iter = std::find_if(_bullets.begin(), _bullets.end(), [](shared_ptr<DunBullet> bullet)-> bool
			{
				if (bullet->_isActive == false)
					return true;

				return false;
			});

		if (iter != _bullets.end())
			(*iter)->Fire(start, direction);
	}
}


