#include "framework.h"
#include "CupHead.h"
#include "CupBullet.h"

CupHead::CupHead()
{
	_col = make_shared<CircleCollider>(50);
	_transform = make_shared<Transform>();
	_bulletSlot = make_shared<Transform>();

	CreateAction("Idle");
	CreateAction("Run");
	CreateAction("Jump");
	CreateAction("AimStraightShot", 0.1f, Action::END);
	_actions[State::ATTACK]->SetEndEvent(std::bind(&CupHead::AttackEnd, this));

	_col->GetTransform()->SetPosition(CENTER);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 20));

	_bulletSlot->SetPosition(Vector2(100, 10));
	_bulletSlot->SetParent(_col->GetTransform());
	_bulletSlot->SetAngle(-PI * 0.75f);

	_effect = make_shared<Effect>("Hit", L"Resource/Texture/hit_4x2.png", Vector2(4, 2), Vector2(300, 300));

	_actions[State::IDLE]->Play();
	_actions[State::RUN]->Play();

	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();

	for (int i = 0; i < 50; i++)
	{
		shared_ptr<CupBullet> bullet = make_shared<CupBullet>();
		_bullets.push_back(bullet);
	}

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.imageSize = _sprites[State::IDLE]->GetImageSize();
	_filterBuffer->_data.selected = 1;
}


CupHead::~CupHead()
{
}

void CupHead::Update()
{
	Input();
	Jump();

	_col->Update();
	_transform->Update();
	_bulletSlot->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		_effect->Play(Vector2(1000.0f, CENTER.y - 100.0f));
	}

	_effect->Update();

	for (shared_ptr<CupBullet> bullet : _bullets)
	{
		bullet->Update();
	}
	_filterBuffer->Update_Resource();
	_filterBuffer->_data.value2 += 1;
}

void CupHead::Render()
{
	_transform->SetWorldBuffer(0);
	_filterBuffer->SetPS_Buffer(2);
	_sprites[_curState]->Render();
	_effect->Render();

	_col->Render();

	for (shared_ptr<CupBullet> bullet : _bullets)
	{
		bullet->Render();
	}
}

void CupHead::PostRender()
{
	//ImGui::SliderInt("selected", &_filterBuffer->_data.selected, 0, 5);
	//ImGui::SliderInt("value1", &_filterBuffer->_data.value1, 0, 300);
	//ImGui::SliderInt("value2", &_filterBuffer->_data.value2, 0, 300);
	//ImGui::SliderInt("value3", &_filterBuffer->_data.value3, 0, 300);
}

void CupHead::Input()
{
	if (KEY_DOWN(VK_LBUTTON) && _isAttack == false)
	{
		Attack();
	}

	if (_isAttack == true)
		return;

	if (KEY_PRESS('A'))
	{
		_col->GetTransform()->AddVector2(-RIGHT_VECTOR * _speed * DELTA_TIME);

		SetLeft();
	}

	if (KEY_PRESS('D'))
	{
		_col->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);

		SetRight();
	}

	if (_curState == State::JUMP || _curState == State::ATTACK)
		return;

	if (KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(State::RUN);
	else if (_curState == State::RUN)
		SetAction(State::IDLE);
}

void CupHead::Jump()
{
	if (_isFalling == true)
		SetAction(State::JUMP);
	else if (_curState == JUMP && _isFalling == false)
		SetAction(State::IDLE);

	_jumpPower -= GRAVITY * 9;

	if (_jumpPower < -_maxFalling)
		_jumpPower = -_maxFalling;

	_col->GetTransform()->AddVector2(Vector2(0.0f, _jumpPower * DELTA_TIME));

	if (KEY_DOWN(VK_SPACE))
	{
		_jumpPower = 1500.0f;
		_isFalling = true;
	}
}

void CupHead::Attack()
{
	SetAction(State::ATTACK);

	_isAttack = true;

	for (shared_ptr<CupBullet> bullet : _bullets)
	{
		if (!bullet->_isActive)
		{
			bullet->_isActive = true;
			bullet->SetDirtection(RIGHT_VECTOR);
			bullet->SetPosition(_bulletSlot->GetWorldPos());
			break;
		}
	}
}

void CupHead::AttackEnd()
{
	_isAttack = false;
	SetAction(State::IDLE);
}

void CupHead::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/CupHead/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/CupHead/" + name + ".xml";
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
	action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	_sprites.push_back(sprite);
}

void CupHead::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

