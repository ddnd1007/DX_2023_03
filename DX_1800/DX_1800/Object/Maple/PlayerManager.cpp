#include "framework.h"
#include "PlayerManager.h"
#include "MapleArrow.h"
#include "MaplePortar.h"
#include "EquipmentInven.h"
#include "MapleInventory.h"
#include "Item.h"
#include "../UI/PlayerHpBar.h"

PlayerManager* PlayerManager::_instance = nullptr;

PlayerManager::PlayerManager()
{
	_circleCol = make_shared<CircleCollider>(30);
	_circleCol->GetTransform()->SetPosition(Vector2(0, 0));
	_transform = make_shared<Transform>();
	_transform->SetPosition(Vector2(0, 0));
	_transform->SetParent(_circleCol->GetTransform());

	_bowCol = make_shared<CircleCollider>(5);
	_bowTrans = make_shared<Transform>();
	_bowCol->GetTransform()->SetParent(_circleCol->GetTransform());

	CreateAction("stand", 0.2f);
	CreateAction("work", 0.1f);
	CreateAction("jump");
	CreateAction("shoot");
	CreateAction("dead");

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

	_inven = make_shared<class MapleInventory>();
	_equip = make_shared<class EquipmentInven>();
	_item = make_shared<class Item>();

	_inven->_col->GetTransform()->AddVector2({ 100.0f,0.0f });
	//SetLeft();

	_inven->_haven[7][0]->SetQuad(L"Resource/Maple/UI/hat.png");
	_inven->_haven[7][0]->SetItemInfo(Item::HAT);


	_inven->_haven[7][1]->SetQuad(L"Resource/Maple/UI/top.png");
	_inven->_haven[7][1]->SetItemInfo(Item::TOP);


	_inven->_haven[7][2]->SetQuad(L"Resource/Maple/UI/pants.png");
	_inven->_haven[7][2]->SetItemInfo(Item::PANTS);


	_inven->_haven[7][3]->SetQuad(L"Resource/Maple/UI/bow.png");
	_inven->_haven[7][3]->SetItemInfo(Item::BOW);

}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Update()
{
	Input();
	Jump();
	IsDead();

	_item->Update();
	_inven->Update();
	_equip->Update();

	_bowCol->Update();
	_circleCol->Update();
	_transform->Update();
	_bowTrans->Update();

	_hpBar->Update();

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


}

void PlayerManager::Render()
{
	_hpBar->PreRender();

	_transform->SetWorldBuffer(0);
	_bowTrans->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_bowCol->Render();
	_circleCol->Render();

	_inven->Render();
	_equip->Render();

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
		_circleCol->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);
		SetLeft();
		_isWork == true;
	}
	if (KEY_PRESS('A'))
	{
		_bowCol->GetTransform()->SetPosition(Vector2(-1, 0));
		_circleCol->GetTransform()->AddVector2(-RIGHT_VECTOR * _speed * DELTA_TIME);
		SetRight();
		_isWork == true;
	}
	if (_curState == State::JUMP)
		return;

	if (KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(State::WORK);
	else if (_curState == State::WORK)
		SetAction(State::STAND);

	if (KEY_DOWN('I') && _inven->active == false)
	{
		_inven->_col->GetTransform()->SetPosition(Vector2(_circleCol->GetWorldPos().x, _circleCol->GetWorldPos().y + 200.0f));
		_inven->active = true;


	}
	else if (KEY_DOWN('I') && _inven->active == true)
	{
		_inven->active = false;
	}

	if (KEY_DOWN('E') && _equip->active == false)
	{
		_equip->_col->GetTransform()->SetPosition(_circleCol->GetWorldPos());
		_equip->active = true;


	}
	else if (KEY_DOWN('E') && _equip->active == true)
	{
		_equip->active = false;
	}
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

	_circleCol->GetTransform()->AddVector2(Vector2(0.0f, _jumpPower * DELTA_TIME));

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

	shared_ptr<MapleArrow> arrows = SetArrows();

	if (_isFalling == false && _isAttack == false)
		SetAction(State::SHOOT);

	for (int i = 0; i < 30; i++)
	{
		_arrows[i]->_isActive = true;
		_arrows[i]->SetPosition(_bowCol->GetWorldPos());

		if (_circleCol->GetWorldPos().x > _bowCol->GetWorldPos().x)
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
		if (_circleCol->GetWorldPos().x > _bowCol->GetWorldPos().x)
		{
			_circleCol->GetTransform()->AddVector2(Vector2(_knockBack, _knockBack * DELTA_TIME));
			SetAction(State::JUMP);
			SetRight();
		}
		else
		{
			_circleCol->GetTransform()->AddVector2(Vector2(-_knockBack, -_knockBack * DELTA_TIME));
			SetAction(State::JUMP);
			SetLeft();
		}
	}
}

shared_ptr<MapleArrow> PlayerManager::SetArrows()
{
	for (auto arrows : _arrows)
	{
		if (arrows->_isActive == true)
			continue;
		else
			return arrows;
	}
	return nullptr;
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
