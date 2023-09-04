#include "framework.h"
#include "PlayerManager.h"
#include "MapleArrow.h"
#include "MaplePortar.h"
#include "MapleInventory.h"
#include "../UI/PlayerHpBar.h"

PlayerManager* PlayerManager::_instance = nullptr;

PlayerManager::PlayerManager()
{
	_col = make_shared<CircleCollider>(30);
	_col->GetTransform()->SetPosition(Vector2(0,0));
	_transform = make_shared<Transform>();
	_transform->SetPosition(Vector2(0, 0));
	_transform->SetParent(_col->GetTransform());

	_bowCol = make_shared<CircleCollider>(5);
	_bowTrans = make_shared<Transform>();
	_bowCol->GetTransform()->SetParent(_col->GetTransform());

	_inven = make_shared<MapleInventory>();

	CreateAction("stand", 0.2f);
	CreateAction("work", 0.1f);
	CreateAction("jump");
	CreateAction("shoot");
	CreateAction("dead");
	CreateAction("lay down");

	_bowTrans->SetParent(_bowCol->GetTransform());
	_bowTrans->SetPosition(Vector2(0, 0));

	_actions[State::STAND]->Play();
	_actions[State::WORK]->Play();

	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<MapleArrow> arrow = make_shared<MapleArrow>();
		_arrows.push_back(arrow);
	}

	_hpBar = make_shared<PlayerHpBar>();
	_hpBar->SetPosition(Vector2(-300.0f, -150.0f));
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Update()
{
	Input();
	Jump();
	IsDead();

	_inven->ToggleInventory();
	
	_bowCol->Update();
	_col->Update();
	_transform->Update();
	_bowTrans->Update();

	_inven->Update();

	for (auto arrow : _arrows)
		arrow->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();

	if (_isInvincible)
	{
		_invincibleTimer -= DELTA_TIME;
		if (_invincibleTimer <= 0.0f)
		{
			_isInvincible = false;
		}
	}

	_hpBar->Update();
}

void PlayerManager::Render()
{
	_hpBar->PostRender();

	_transform->SetWorldBuffer(0);
	_bowTrans->SetWorldBuffer(0);
	_sprites[_curState]->Render();


	_bowCol->Render();
	_col->Render();
	
	_inven->Render();

	for (auto arrow : _arrows)
		arrow->Render();
}

void PlayerManager::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void PlayerManager::Input()
{
	if (KEY_PRESS(VK_LCONTROL) && _isFalling == false && _isAttack == false)
	{
		Attack();
	}
	else if (KEY_UP(VK_LCONTROL))
	{
		EndAttack();
	}
	if (KEY_PRESS('D'))
	{
		_bowCol->GetTransform()->SetPosition(Vector2(1, 0));
		_col->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);
		SetLeft();
		_isWork == true;
	}
	if (KEY_PRESS('A'))
	{
		_bowCol->GetTransform()->SetPosition(Vector2(-1, 0));
		_col->GetTransform()->AddVector2(-RIGHT_VECTOR * _speed * DELTA_TIME);
		SetRight();
		_isWork == true;
	}
	if (_curState == State::JUMP)
		return;

	if (KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(State::WORK);
	else if (_curState == State::WORK)
		SetAction(State::STAND);

}

void PlayerManager::Jump()
{
	if (_isFalling == true && _isAttack == false)
		SetAction(State::JUMP);
	else if (_curState == JUMP && _isFalling == false && _isAttack == false)
		SetAction(State::STAND);

	_jumpPower -= GRAVITY * 9;

	if (_jumpPower < -_maxFalling)
		_jumpPower = -_maxFalling;

	_col->GetTransform()->AddVector2(Vector2(0.0f, _jumpPower * DELTA_TIME));

	if (KEY_DOWN(VK_SPACE) && _isAttack == false && IsActive() == true)
	{
		_jumpPower = 1200.0f;
		_isFalling = true;
	}
}

void PlayerManager::Attack()
{
	if (IsActive() == false)
		return;

	if (_isFalling == false && _isAttack == false)
		SetAction(State::SHOOT);

	for (int i = 0; i < 30; i++)
	{
		_arrows[i]->_isActive = true;
		_arrows[i]->SetPosition(_bowCol->GetWorldPos());

		if (_col->GetWorldPos().x > _bowCol->GetWorldPos().x)
		{
			_arrows[i]->SetPosition(_bowCol->GetWorldPos());
			_arrows[i]->SetDirtection(-RIGHT_VECTOR);
		}
		else
		{
			_arrows[i]->SetPosition(_bowCol->GetWorldPos());
			_arrows[i]->SetDirtection(RIGHT_VECTOR);
		}

		_isAttack = true;
	}
}

void PlayerManager::EndAttack()
{
	if (IsActive() == false)
		return;

	_isAttack = false;
	SetAction(State::WORK);
}

bool PlayerManager::IsDead()
{
	if (IsActive() == true)
		return _hp > 0;

	if (IsActive() == false)
	{
		SetAction(State::DEAD);
		_isFalling == false && _isAttack == false && _isWork == false;
	}
}

void PlayerManager::TakeDamage(int damage)
{
	if (IsActive() == false)
		return;

	if (!_isInvincible)
	{
		_hp -= damage;
		_hpBar->SetRatio(_hp / (float)_maxHp);
		_isInvincible = true;
		_invincibleTimer = _invincibleDuration;
		_knockBack = 100;
		_knockBack -= GRAVITY * 7;
		if (_col->GetWorldPos().x > _bowCol->GetWorldPos().x)
		{
			_col->GetTransform()->AddVector2(Vector2(_knockBack, _knockBack * DELTA_TIME));
			SetAction(State::JUMP);
			SetRight();
		}
		else
		{
			_col->GetTransform()->AddVector2(Vector2(-_knockBack, -_knockBack * DELTA_TIME));
			SetAction(State::JUMP);
			SetLeft();
		}
	}
}

void PlayerManager::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Maple/Character/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Maple/Character/" + name + ".xml";
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;
	float averageW = 0;
	float averageH = 0;
	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		averageW += w;
		averageH += h;
		count++;

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, name, type, speed);
	//action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	sprite->SetPS(ADD_PS(L"Shader/ActionPS.hlsl"));
	_sprites.push_back(sprite);
}
